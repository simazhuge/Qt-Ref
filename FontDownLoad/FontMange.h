#ifndef FONTMANGE_H
#define FONTMANGE_H

#include <QObject>
/*
* Description:
* Author    Version    Date        Record
* Liyong   1        2020-11-23   版本创建
*/
class FontMange : public QObject
{
    Q_OBJECT
public:
    explicit FontMange(QObject *parent = nullptr);
    static FontMange *getInstance();
    class GarbageCollector {
    public:
        ~GarbageCollector();
    };
    void loadFontFile();
signals:

};

#endif // FONTMANGE_H
