#pragma once

#include "ffmpeg_avframe.h"

class FFmpegFrameSink
{
public:
    virtual ~FFmpegFrameSink() = default;

public:
    virtual void setCodecpar(const AVCodecParameters *codecpar) = 0;
    virtual void handleFrame(const FFmpegAVFrame *frame)        = 0;
};
