#pragma once

#include "ffmpeg_frame_sink.h"

class JpegFrameSink : public FFmpegFrameSink
{
public:
    JpegFrameSink();
    ~JpegFrameSink();

public:
    void handleFrame(const FFmpegAVFrame *frame) override;
};
