#pragma once

#include "ffmpeg_avpacket.h"
#include "ffmpeg_decoder.h"
#include "ffmpeg_frame_sink.h"

#include <functional>
#include <memory>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

class FFmpegAVStream
{
    using PacketCallback = std::function<void(const FFmpegAVPacket *)>;

public:
    FFmpegAVStream(AVFormatContext *format_ctx, AVStream *stream);
    ~FFmpegAVStream();

public:
    void setCallback(PacketCallback cb);
    void setFrameSink(const std::shared_ptr<FFmpegFrameSink> &frame_sink);
    void decodePacket(FFmpegAVPacket *pkt);

    int         getStreamIndex() const;
    AVMediaType getMediaType() const;
    AVCodecID   getCodecID() const;
    const char *getMediaTypeName() const;
    const char *getCodecName() const;

private:
    AVFormatContext                 *format_ctx_;
    AVStream                        *av_stream_;
    PacketCallback                   packet_cb_;
    std::shared_ptr<FFmpegDecoder>   decoder_;
    std::shared_ptr<FFmpegFrameSink> frame_sink_;
};