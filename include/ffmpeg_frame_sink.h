#pragma once

#include "ffmpeg_avframe.h"

class FFmpegFrameSink
{
public:
    virtual ~FFmpegFrameSink() = default;

public:
    virtual void handleFrame(const FFmpegAVFrame *frame) = 0;
};