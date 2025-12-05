#pragma once

#include "ffmpeg_avframe.h"
#include "ffmpeg_avpacket.h"
#include "ffmpeg_frame_sink.h"

extern "C"
{
#include <libavcodec/avcodec.h>
}

class FFmpegDecoder
{
public:
    FFmpegDecoder(const AVCodecParameters *codecpar);
    ~FFmpegDecoder();

public:
    void decode(FFmpegAVPacket *pkt, FFmpegFrameSink *sink);

private:
    AVCodecContext *stream_ctx_;
    FFmpegAVFrame   frame_;
};