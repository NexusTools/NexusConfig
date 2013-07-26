#ifndef NEXUSCONFIG_H
#define NEXUSCONFIG_H

#include "nexusconfig_global.h"

#include <QBuffer>
#include <QVariantMap>

class NexusConfig
{

    enum Format {
        IniFormat,
        XmlFormat,
        JSONFormat,
        YMLFormat,// TODO: Implement
        BinaryFormat = 0x10,

        DetectFormat = 0xff
    };

public:
    NexusConfig();

    QVariant parse(QIODevice&, Format format=DetectFormat);
    QVariant parse(QByteArray data, Format format=DetectFormat) {
        QBuffer buffer(&data);
        buffer.open(QIODevice::ReadOnly);
        return parse(buffer, format);
    }
    QVariant parse(QString data, Format format=DetectFormat) {return parse(data.toUtf8(), format);}

private:
    QVariantMap defaults;
    QVariantMap current;
};

#endif // NEXUSCONFIG_H
