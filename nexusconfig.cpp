#include "nexusconfig.h"

NexusConfig::NexusConfig()
{
}

QVariant NexusConfig::parse(QIODevice & io, Format f) {
    QVariant data;

    switch(f) {
        case DetectFormat:
        {
            if(io.isSequential())
                throw "Sequential devices cannot be used when detecting the configuration format.";

            try {
                return parse(io, BinaryFormat);
            } catch(const char* e) {}
            try {
                return parse(io, XmlFormat);
            } catch(const char* e) {}
            try {
                return parse(io, YMLFormat);
            } catch(const char* e) {}
            try {
                return parse(io, IniFormat);
            } catch(const char* e) {}
            try {
                return parse(io, JSONFormat);
            } catch(const char* e) {}

            throw "No supported format detected.";
            break;
        }

        case BinaryFormat:
        {
            if(io.read(6) != "NCST\x96\xef")
                throw "Binary config header mismatch.";
            QDataStream dstream(&io);
            dstream >> data;
            if(dstream.status() != QDataStream::Ok)
                throw "Binary config corrupt.";
            break;
        }

        default:
            throw "Unsupported format requested.";
    }

    return data;
}
