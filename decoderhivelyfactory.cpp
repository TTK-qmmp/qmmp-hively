#include "decoderhivelyfactory.h"
#include "hivelymetadatamodel.h"
#include "hivelyhelper.h"
#include "decoder_hively.h"

#include <QMessageBox>

bool DecoderHivelyFactory::canDecode(QIODevice *input) const
{
    QFile *file = static_cast<QFile*>(input);
    if(!file)
    {
        return false;
    }

    HivelyHelper helper(file->fileName());
    return helper.initialize();
}

DecoderProperties DecoderHivelyFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("Hively Plugin");
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

    if(parts & TrackInfo::MetaData)
    {
        info->setValue(Qmmp::TITLE, helper.title());
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.depth());
        info->setValue(Qmmp::FORMAT_NAME, "Hively");
        info->setDuration(helper.totalTime());
    }
    return QList<TrackInfo*>() << info;
}

MetaDataModel* DecoderHivelyFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(readOnly);
    return new HivelyMetaDataModel(path);
}

void DecoderHivelyFactory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}

void DecoderHivelyFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About HVL Module Reader Plugin"),
                       tr("Qmmp HVL Module Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderHivelyFactory::translation() const
{
    return QString();
}
