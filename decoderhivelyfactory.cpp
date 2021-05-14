#include "hivelyhelper.h"
#include "decoder_hively.h"
#include "decoderhivelyfactory.h"

#include <QMessageBox>

bool DecoderHivelyFactory::canDecode(QIODevice *) const
{
    return false;
}

DecoderProperties DecoderHivelyFactory::properties() const
{
    DecoderProperties properties;
    properties.name = "Hively Plugin";
    properties.shortName = "hively";
    properties.filters << "*.ahx" << "*.hvl";
    properties.description = "HVL Module File";
    properties.protocols << "file";
    properties.noInput = true;
    return properties;
}

Decoder *DecoderHivelyFactory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderHively(path);
}

QList<TrackInfo*> DecoderHivelyFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);

    if(parts == TrackInfo::Parts())
    {
        return QList<TrackInfo*>() << info;
    }

    HivelyHelper helper(path);
    if(!helper.initialize())
    {
        delete info;
        return QList<TrackInfo*>();
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.bitsPerSample());
        info->setValue(Qmmp::FORMAT_NAME, "Hively");
        info->setDuration(helper.totalTime());
    }

    return QList<TrackInfo*>() << info;
}

MetaDataModel* DecoderHivelyFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(path);
    Q_UNUSED(readOnly);
    return nullptr;
}

void DecoderHivelyFactory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}

void DecoderHivelyFactory::showAbout(QWidget *parent)
{
    QMessageBox::about (parent, tr("About HVL Module Reader Plugin"),
                        tr("Qmmp HVL Module Reader Plugin")+"\n"+
                        tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderHivelyFactory::translation() const
{
    return QString();
}
