#include "jpeg_frame_sink.h"

#include <glog/logging.h>
#include <opencv2/opencv.hpp>

static cv::Mat yuv420p_to_bgr(int width, int height, const uint8_t *yuv420p, int yuv_size)
{
    int uvwidth  = width / 2;
    int uvheight = height / 2;
    int size     = width * height;
    int uvsize   = uvwidth * uvheight;

    cv::Mat yuv_data(cv::Size(width, height + uvheight), CV_8UC1);
    memcpy(yuv_data.data, yuv420p, size + uvsize * 2);

    cv::Mat bgr_data(cv::Size(width, height), CV_8UC3);
    cv::cvtColor(yuv_data, bgr_data, cv::COLOR_YUV2BGR_I420);
    return bgr_data;
}

static AVPixelFormat convert_deprecated_format(enum AVPixelFormat format)
{
    switch (format) {
        case AV_PIX_FMT_YUVJ420P:
            return AV_PIX_FMT_YUV420P;
            break;
        case AV_PIX_FMT_YUVJ422P:
            return AV_PIX_FMT_YUV422P;
            break;
        case AV_PIX_FMT_YUVJ444P:
            return AV_PIX_FMT_YUV444P;
            break;
        case AV_PIX_FMT_YUVJ440P:
            return AV_PIX_FMT_YUV440P;
            break;
        default:
            return format;
            break;
    }
}

JpegFrameSink::JpegFrameSink(int width, int height) : img_convert_ctx_(nullptr), bgr_buffer_size_(0)
{
    bgr_frame_       = std::make_shared<FFmpegAVFrame>(width, height, AV_PIX_FMT_BGR24);
    bgr_buffer_size_ = bgr_frame_->bufSize(16);
}

JpegFrameSink::~JpegFrameSink()
{
    if (img_convert_ctx_) {
        sws_freeContext(img_convert_ctx_);
    }
}

void JpegFrameSink::setCodecpar(const AVCodecParameters *codecpar)
{
    if (img_convert_ctx_) {
        sws_freeContext(img_convert_ctx_);
    }
    img_convert_ctx_ = sws_getContext(codecpar->width,
                                      codecpar->height,
                                      convert_deprecated_format((AVPixelFormat)codecpar->format),
                                      bgr_frame_->width(),
                                      bgr_frame_->height(),
                                      bgr_frame_->format(),
                                      SWS_BICUBIC,
                                      nullptr,
                                      nullptr,
                                      nullptr);
}

void JpegFrameSink::handleFrame(const FFmpegAVFrame *frame)
{
    LOG(INFO) << "JpegFrameSink::handleFrame";

    sws_scale(img_convert_ctx_,
              frame->frame()->data,
              frame->frame()->linesize,
              0,
              frame->height(),
              bgr_frame_->frame()->data,
              bgr_frame_->frame()->linesize);

    cv::Mat bgrImage(cv::Size(bgr_frame_->width(), bgr_frame_->height()), CV_8UC3);
    memcpy(bgrImage.data, bgr_frame_->frame()->data[0], bgr_buffer_size_);

    cv::imshow("result", bgrImage);
    cv::waitKey(50);
}