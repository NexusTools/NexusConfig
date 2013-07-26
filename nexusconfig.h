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

    inline QVariant parse(Format f=DetectFormat) {return parseFile(filePath, f);}

    static QVariant parseFile(QString f, Format format=DetectFormat);
    static QVariant parse(QIODevice&, Format format=DetectFormat);
    static inline QVariant parse(QByteArray data, Format format=DetectFormat) {
        QBuffer buffer(&data);
        buffer.open(QIODevice::ReadOnly);
        return parse(buffer, format);
    }
    static inline QVariant parse(QString data, Format format=DetectFormat) {return parse(data.toUtf8(), format);}

private:
    QVariantMap defaults;
    QVariantMap current;

    QString filePath;
};

#endif // NEXUSCONFIG_H
