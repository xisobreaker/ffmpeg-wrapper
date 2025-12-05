#pragma once

#include <string>

extern "C"
{
#include <libavformat/avformat.h>
}

class FFmpegAVFrame
{
public:
    FFmpegAVFrame();
    explicit FFmpegAVFrame(AVFrame *frame);
    explicit FFmpegAVFrame(int width, int height, AVPixelFormat format);
    ~FFmpegAVFrame();

public:
    AVFrame      *frame() const;
    int           width() const;
    AVPixelFormat format() const;
    std::string   formatName() const;
    int           height() const;
    void          unref();
    int           bufSize(int align = 16);

private:
    AVFrame *av_frame_;
};