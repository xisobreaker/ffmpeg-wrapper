#include "ffmpeg_avstream.h"

#include <glog/logging.h>

FFmpegAVStream::FFmpegAVStream(AVFormatContext *format_ctx, AVStream *stream) : format_ctx_(format_ctx), av_stream_(stream)
{
    decoder_ = std::make_shared<FFmpegDecoder>(av_stream_->codecpar);
}

FFmpegAVStream::~FFmpegAVStream()
{
}

/**
 * @brief 设置 packet 解码前回调.
 *
 * @param cb 回调函数.
 */
void FFmpegAVStream::setCallback(PacketCallback cb)
{
    packet_cb_ = cb;
}

void FFmpegAVStream::setFrameSink(const std::shared_ptr<FFmpegFrameSink> &frame_sink)
{
    frame_sink_ = frame_sink;
    if (frame_sink_) {
        frame_sink_->setCodecpar(av_stream_->codecpar);
    }
}

/**
 * @brief 解码 packet.
 *
 * @param pkt packet.
 */
void FFmpegAVStream::decodePacket(FFmpegAVPacket *pkt)
{
    if (packet_cb_)
        packet_cb_(pkt);

    if (frame_sink_) {
        decoder_->decode(pkt, frame_sink_.get());
    }
}

/**
 * @brief 获取 stream index.
 *
 * @return int stream index.
 */
int FFmpegAVStream::getStreamIndex() const
{
    return av_stream_->index;
}

/**
 * @brief 获取 media type.
 *
 * @return AVMediaType media type.
 */
AVMediaType FFmpegAVStream::getMediaType() const
{
    return av_stream_->codecpar->codec_type;
}

/**
 * @brief 获取 codec id.
 *
 * @return AVCodecID codec id.
 */
AVCodecID FFmpegAVStream::getCodecID() const
{
    return av_stream_->codecpar->codec_id;
}

/**
 * @brief 获取 media type name.
 *
 * @return const char* media type name.
 */
const char *FFmpegAVStream::getMediaTypeName() const
{
    return av_get_media_type_string(av_stream_->codecpar->codec_type);
}

/**
 * @brief 获取 codec name.
 *
 * @return const char* codec name.
 */
const char *FFmpegAVStream::getCodecName() const
{
    return avcodec_get_name(av_stream_->codecpar->codec_id);
}
