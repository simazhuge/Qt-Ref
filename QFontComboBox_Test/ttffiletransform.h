#ifndef TTFFILETRANSFORM_H
#define TTFFILETRANSFORM_H

#include <QString>
class TTFFileTransForm
{
public:
    TTFFileTransForm();
    static bool transFile(const QString& inFile, const QString &outFile, quint16 familyId);
};

#endif // TTFFILETRANSFORM_H
