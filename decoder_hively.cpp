#include "decoder_hively.h"
#include "hivelyhelper.h"

DecoderHively::DecoderHively(const QString &path)
    : Decoder()
{
    m_helper = new HivelyHelper(path);
}

DecoderHively::~DecoderHively()
{
    delete m_helper;
}

bool DecoderHively::initialize()
{
    if(!m_helper->initialize())
    {
        qWarning("DecoderHively: initialize failed");
        return false;
    }

    const int rate = m_helper->sampleRate();
    const int channels = m_helper->channels();
    if(rate == 0 || channels == 0)
    {
        qWarning("DecoderHively: rate or channel invalid");
        return false;
    }

    configure(rate, channels, Qmmp::PCM_S16LE);
    qDebug("DecoderHively: initialize success");
    return true;
}

qint64 DecoderHively::totalTime() const
{
    return m_helper->totalTime();
}

int DecoderHively::bitrate() const
{
    return m_helper->bitrate();
}

qint64 DecoderHively::read(unsigned char *data, qint64 maxSize)
{
    return m_helper->read(data, maxSize);
}

void DecoderHively::seek(qint64 time)
{
    m_helper->seek(time);
}
