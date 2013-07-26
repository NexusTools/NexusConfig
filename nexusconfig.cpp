#include "nexusconfig.h"

#ifdef QSETTINGSLOCATION
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#else
#include <QStandardPaths>
#endif

#include <QCoreApplication>
#include <QDomDocument>
#include <QDebug>
#include <QFile>

NexusConfig::NexusConfig(QString appName, QString organization)
{
    if(appName.isEmpty())
        appName = QCoreApplication::instance()->applicationName();
    if(organization.isEmpty())
        organization = QCoreApplication::instance()->organizationName();

    filePath =
#ifdef QSETTINGSLOCATION
            QSettings(organization, appName).fileName();
#else
            QStandardPaths::locate(QStandardPaths::ConfigLocation, QString("%1/%2.conf").arg(organization).arg(appName));
#endif
    qDebug() << filePath;

    try {
        parse();
    } catch(const char* err) {
        qWarning() << err;
    } catch(...) {}
}

QVariant NexusConfig::parseFile(QString p, Format f) {
    QFile file(p);
    qDebug() << "Parsing configuration file..." << p.toLocal8Bit().data();
    if(file.open(QFile::ReadOnly))
        return parse(file, f);
    else
        throw "Failed to open configuration file...";
}

QVariant nodeToVariant(QDomNode el) {
    if(el.hasAttributes() || el.hasChildNodes()) {
        QVariantMap map;
        if(el.attributes().length()) {
            for(int i=0; i<el.attributes().length(); i++)
                map.insert(el.attributes().item(i).nodeName(), nodeToVariant(el.attributes().item(i)));

        } else if(el.nodeName().endsWith('s')) {
            QVariantList list;
            QString listNodeName = el.nodeName().mid(0, el.nodeName().length()-1);
            for(int i=0; i<el.childNodes().length(); i++) {
                if(el.childNodes().at(i).nodeName() != listNodeName) {
                    list.clear();
                    break;
                }
                list.append(nodeToVariant(el.childNodes().at(i)));
            }

            if(!list.isEmpty())
                return list;
        }

        for(int i=0; i<el.childNodes().length(); i++)
            map.insert(el.childNodes().at(i).nodeName(), nodeToVariant(el.childNodes().at(i)));

        if(map.size() == 1 && map.contains("#text"))
            return map.value("#text");
        return map;
    } else
        return el.nodeValue();
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

        case XmlFormat:
        {
            QString err;
            QDomDocument dom;
            if(!dom.setContent(&io, &err))
                throw err.toLocal8Bit().data();

            QDomNode configNode = dom.firstChild();

            while(!configNode.isNull() && configNode.nodeName() !=
                    QCoreApplication::instance()->applicationName())
                configNode = configNode.nextSibling();

            if(configNode.isNull())
                throw "Could not find root node.";

            if(configNode.hasAttributes())
                throw "Root node may not have attributes.";
            return nodeToVariant(configNode);
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
