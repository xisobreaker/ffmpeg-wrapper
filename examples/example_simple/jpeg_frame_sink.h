#pragma once

#include "ffmpeg_avframe.h"
#include "ffmpeg_frame_sink.h"

#include <memory>

extern "C"
{
#include <libswscale/swscale.h>
}

class JpegFrameSink : public FFmpegFrameSink
{
public:
    JpegFrameSink(int width, int height);
    ~JpegFrameSink();

public:
    void setCodecpar(const AVCodecParameters *codecpar) override;
    void handleFrame(const FFmpegAVFrame *frame) override;

private:
    std::shared_ptr<FFmpegAVFrame> bgr_frame_;
    int                            bgr_buffer_size_;
    SwsContext                    *img_convert_ctx_;
};
