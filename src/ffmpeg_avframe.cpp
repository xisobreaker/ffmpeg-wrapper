#include "ffmpeg_avframe.h"

#include <stdexcept>

extern "C"
{
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libavutil/pixdesc.h>
}

FFmpegAVFrame::FFmpegAVFrame() : av_frame_(av_frame_alloc())
{
    if (!av_frame_) {
        throw std::runtime_error("Can't alloc AVFrame!");
    }
}

FFmpegAVFrame::FFmpegAVFrame(AVFrame *frame) : av_frame_(frame)
{
}

FFmpegAVFrame::FFmpegAVFrame(int width, int height, AVPixelFormat format) : av_frame_(av_frame_alloc())
{
    if (!av_frame_) {
        throw std::runtime_error("Can't alloc AVFrame!");
    }
    resize(width, height, format, 0);
}

FFmpegAVFrame::~FFmpegAVFrame()
{
    av_frame_free(&av_frame_);
}

void FFmpegAVFrame::resize(int width, int height, AVPixelFormat format, int align)
{
    av_frame_->width  = width;
    av_frame_->height = height;
    av_frame_->format = format;
    av_frame_get_buffer(av_frame_, align);
}

AVFrame *FFmpegAVFrame::frame() const
{
    return av_frame_;
}

int FFmpegAVFrame::width() const
{
    return av_frame_->width;
}

int FFmpegAVFrame::height() const
{
    return av_frame_->height;
}

AVPixelFormat FFmpegAVFrame::format() const
{
    return static_cast<AVPixelFormat>(av_frame_->format);
}

std::string FFmpegAVFrame::formatName() const
{
    return av_get_pix_fmt_name(static_cast<AVPixelFormat>(av_frame_->format));
}

void FFmpegAVFrame::unref()
{
    av_frame_unref(av_frame_);
}

/**
 * @brief 计算 AVFrame 占用的内存大小
 *
 * @param align 对齐字节数，默认16
 * @return int 内存大小
 */
int FFmpegAVFrame::bufSize(int align)
{
    return av_image_get_buffer_size((AVPixelFormat)av_frame_->format, av_frame_->width, av_frame_->height, align);
}
