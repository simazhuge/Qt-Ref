#include "ttffiletransform.h"
#include <QtCore/qt_windows.h>
#include <QtEndian>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QList>
TTFFileTransForm::TTFFileTransForm()
{

}

struct XFontNames {
    QString name;   // e.g. "DejaVu Sans Condensed"
    QString style;  // e.g. "Italic"
    QString preferredName;  // e.g. "DejaVu Sans"
    QString preferredStyle; // e.g. "Condensed Italic"
};

#define MAKE_TAG(ch1, ch2, ch3, ch4) (\
    (((quint32)(ch4)) << 24) | \
    (((quint32)(ch3)) << 16) | \
    (((quint32)(ch2)) << 8) | \
    ((quint32)(ch1)) \
    )
static QList<quint32> getTrueTypeFontOffsets(const uchar *fontData)
{
    QList<quint32> offsets;
    const quint32 headerTag = *reinterpret_cast<const quint32 *>(fontData);
    if (headerTag != MAKE_TAG('t', 't', 'c', 'f')) {
        if (headerTag != MAKE_TAG(0, 1, 0, 0)
            && headerTag != MAKE_TAG('O', 'T', 'T', 'O')
            && headerTag != MAKE_TAG('t', 'r', 'u', 'e')
            && headerTag != MAKE_TAG('t', 'y', 'p', '1'))
            return offsets;
        offsets << 0;
        return offsets;
    }
    const quint32 numFonts = qFromBigEndian<quint32>(fontData + 8);
    for (uint i = 0; i < numFonts; ++i) {
        offsets << qFromBigEndian<quint32>(fontData + 12 + i * 4);
    }
    return offsets;
}

static void getFontTable( uchar *fileBegin,  uchar *data, quint32 tag,  uchar **table, quint32 *length)
{
    const quint16 numTables = qFromBigEndian<quint16>(data + 4);
    for (uint i = 0; i < numTables; ++i) {
        const quint32 offset = 12 + 16 * i;
        if (*reinterpret_cast<const quint32 *>(data + offset) == tag) {
            *table = fileBegin + qFromBigEndian<quint32>(data + offset + 8);
            *length = qFromBigEndian<quint32>(data + offset + 12);
            return;
        }
    }
    *table = 0;
    *length = 0;
    return;
}
inline quint16 xt_getUShort(const unsigned char *p)
{
    quint16 val;
    val = *p++ << 8;
    val |= *p;

    return val;
}

inline quint16 qt_getUShort2(const unsigned char *p)
{
    quint16 val(0);
    val = *p++ ;
    val |= *p << 8;

    return val;
}
enum XFieldTypeValue {
    FamilyId = 1,
    StyleId = 2,
    PreferredFamilyId = 16,
    PreferredStyleId = 17,
};

enum XPlatformFieldValue {
    PlatformId_Unicode = 0,
    PlatformId_Apple = 1,
    PlatformId_Microsoft = 3
};

static QString readName(bool unicode, const uchar *string, int length)
{
    QString out;
    if (unicode) {
        // utf16

        length /= 2;
        out.resize(length);
        QChar *uc = out.data();
        for (int i = 0; i < length; ++i)
            uc[i] = xt_getUShort(string + 2*i);
    } else {
        // Apple Roman

        out.resize(length);
        QChar *uc = out.data();
        for (int i = 0; i < length; ++i)
            uc[i] = QLatin1Char(char(string[i]));
    }
    return out;
}

static void writeName(bool unicode,  uchar *string, int length, quint16 id)
{

    if (unicode) {
        // utf16
        auto str = QString::number(id);

        auto uc = (quint8 *)str.data();
        length /= 2;
        for (int i = 0; i < length; ++i)
        {
            quint8 a = *(uc + 2 *i);
            quint8 b = *(uc+1 + 2 *i);
            quint16 data = (a << 8) | b;
            memcpy(string + 2 *i, &data,  sizeof(quint16));
        }

    } else {
        // Apple Roman

        auto str = QString::number(id);
        auto d = (quint8 *)str.data();
        for (int i = 0; i < length; ++i)
            memcpy(string + i, &d, sizeof(quint8));
//        out.resize(length);
//        QChar *uc = out.data();
//        for (int i = 0; i < length; ++i)
//            uc[i] = QLatin1Char(char(string[i]));
    }

}

XFontNames xt_getCanonicalXFontNames(uchar *table, quint32 bytes, quint16 unitId)
{
    XFontNames out;
    const int NameRecordSize = 12;
    const int MS_LangIdEnglish = 0x009;

    // get the name table
    quint16 count;
    quint16 string_offset;
    unsigned char *names;

    if (bytes < 8)
        return out;

    if (xt_getUShort(table) != 0)
        return out;

    count = xt_getUShort(table + 2);
    string_offset = xt_getUShort(table + 4);
    names = table + 6;

    if (string_offset >= bytes || 6 + count*NameRecordSize > string_offset)
        return out;

    enum PlatformIdType {
        NotFound = 0,
        Unicode = 1,
        Apple = 2,
        Microsoft = 3
    };

    PlatformIdType idStatus[4] = { NotFound, NotFound, NotFound, NotFound };
    int ids[4] = { -1, -1, -1, -1 };

    for (int i = 0; i < count; ++i) {
        // search for the correct name entries

        quint16 platform_id = xt_getUShort(names + i*NameRecordSize);
        quint16 encoding_id = xt_getUShort(names + 2 + i*NameRecordSize);
        quint16 language_id = xt_getUShort(names + 4 + i*NameRecordSize);
        quint16 name_id = xt_getUShort(names + 6 + i*NameRecordSize);

        PlatformIdType *idType = nullptr;
        int *id = nullptr;

        switch (name_id) {
        case FamilyId:
            idType = &idStatus[0];
            id = &ids[0];
            break;
        case StyleId:
            idType = &idStatus[1];
            id = &ids[1];
            break;
        case PreferredFamilyId:
            idType = &idStatus[2];
            id = &ids[2];
            break;
        case PreferredStyleId:
            idType = &idStatus[3];
            id = &ids[3];
            break;
        default:
            continue;
        }


        quint16 length = xt_getUShort(names + 8 + i*NameRecordSize);
        quint16 offset = xt_getUShort(names + 10 + i*NameRecordSize);
        if (DWORD(string_offset + offset + length) > bytes)
            continue;

        if ((platform_id == PlatformId_Microsoft
            && (encoding_id == 0 || encoding_id == 1))
            && (language_id & 0x3ff) == MS_LangIdEnglish
            && *idType < Microsoft) {
            *id = i;
            *idType = Microsoft;

        }
        // not sure if encoding id 4 for Unicode is utf16 or ucs4...
        else if (platform_id == PlatformId_Unicode && encoding_id < 4 && *idType < Unicode) {
            *id = i;
            *idType = Unicode;
        }
        else if (platform_id == PlatformId_Apple && encoding_id == 0 && language_id == 0 && *idType < Apple) {
            *id = i;
            *idType = Apple;
        }

        if(name_id != StyleId && FamilyId != PreferredStyleId)
        {
            auto num = QString::number(unitId).length() * 2;
            auto lenght2 = qToBigEndian<quint16>(num); // 只设置前4个字节
            memcpy(names + 8 + i*NameRecordSize,  &lenght2, sizeof (quint16));
            quint16 length2 = xt_getUShort(names + 8 + i*NameRecordSize);

            quint16 length = xt_getUShort(names +  8 + i * NameRecordSize);
            quint16 offset = xt_getUShort(names + 10 + i * NameRecordSize);
            unsigned char *string = table + string_offset + offset;
            writeName(idStatus[i] != Apple, string, length, unitId);
        }
    }

    QString strings[4];
    for (int i = 0; i < 4; ++i) {
        if (idStatus[i] == NotFound)
            continue;
        int id = ids[i];
        quint16 length = xt_getUShort(names +  8 + id * NameRecordSize);
        quint16 offset = xt_getUShort(names + 10 + id * NameRecordSize);
        const unsigned char *string = table + string_offset + offset;
        strings[i] = readName(idStatus[i] != Apple, string, length);
    }

    out.name = strings[0];
    out.style = strings[1];
    out.preferredName = strings[2];
    out.preferredStyle = strings[3];
    return out;
}

static void getFamiliesAndSignatures(QByteArray &fontData,
                                     QList<XFontNames> *families,
                                     QVector<FONTSIGNATURE> *signatures,
                                     int id) //设置字体的 id
{
    uchar *data = reinterpret_cast<uchar *>(fontData.data());

    QList<quint32> offsets = getTrueTypeFontOffsets(data);
    if (offsets.isEmpty())
        return;

    for (int i = 0; i < offsets.count(); ++i) {
        uchar *font = data + offsets.at(i);
        uchar *table;
        quint32 length;
        getFontTable(data, font, MAKE_TAG('n', 'a', 'm', 'e'), &table, &length);
        if (!table)
            continue;
        XFontNames names = xt_getCanonicalXFontNames(table, length, id);
        if (names.name.isEmpty())
            continue;

        families->append(qMove(names));

        if (signatures) {
            FONTSIGNATURE signature;
            getFontTable(data, font, MAKE_TAG('O', 'S', '/', '2'), &table, &length);
            if (table && length >= 86) {
                // Offsets taken from OS/2 table in the TrueType spec
                signature.fsUsb[0] = qFromBigEndian<quint32>(table + 42);
                signature.fsUsb[1] = qFromBigEndian<quint32>(table + 46);
                signature.fsUsb[2] = qFromBigEndian<quint32>(table + 50);
                signature.fsUsb[3] = qFromBigEndian<quint32>(table + 54);

                signature.fsCsb[0] = qFromBigEndian<quint32>(table + 78);
                signature.fsCsb[1] = qFromBigEndian<quint32>(table + 82);
            } else {
                memset(&signature, 0, sizeof(signature));
            }
            signatures->append(signature);
        }
    }
}

bool TTFFileTransForm::transFile(const QString &inFile, const QString &outFile, quint16 familyId)
{
    QFileInfo info(inFile);
    if(info.suffix() != "ttf")
    {
        return false;
    }
    if(familyId > 99)
    {
        qDebug() << "error familyId";
        return false;
    }
    QVector<FONTSIGNATURE> signatures;
    QList<XFontNames> families;
    QFile file(inFile);
    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "open file error:" << inFile;
        return false;
    }
    QFile file2(outFile);
    if(!file2.open(QFile::WriteOnly))
    {
        qDebug() << "open file error:" << outFile;
        return false;
    }
    auto temp = file.readAll();
    file.close();
    getFamiliesAndSignatures(temp, &families, &signatures, familyId);
    file2.write(temp);
    file2.close();

    return true;
}








