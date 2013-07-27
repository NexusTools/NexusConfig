#ifndef NEXUSCONFIG_H
#define NEXUSCONFIG_H

#include "nexusconfig_global.h"

#include <QBuffer>
#include <QVariantMap>

class NexusConfig
{
public:
    enum Format {
        IniFormat,
        XmlFormat,
        JSONFormat,
        YMLFormat,
        SQLFormat,
        BinaryFormat = 0x10,

        DetectFormat = 0xff
    };

    NexusConfig(QString appName =QString(), QString organization =QString());

    inline QVariant parse(Format f=DetectFormat, QString name =QString()) {return parseFile(filePath, f, name);}

    static QVariant parseFile(QString f, Format format=DetectFormat, QString name =QString());
    static QVariant parse(QIODevice&, Format format=DetectFormat, QString name =QString());
    static inline QVariant parse(QByteArray data, Format format=DetectFormat, QString name =QString()) {
        QBuffer buffer(&data);
        buffer.open(QIODevice::ReadOnly);
        return parse(buffer, format, name);
    }
    static inline QVariant parse(QString data, Format format=DetectFormat, QString name =QString()) {return parse(data.toUtf8(), format, name);}

private:
    QVariantMap defaults;
    QVariantMap current;

    QString filePath;
};

#endif // NEXUSCONFIG_H
