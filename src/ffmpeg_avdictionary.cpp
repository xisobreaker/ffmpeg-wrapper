#include "ffmpeg_avdictionary.h"

FFmpegAVDictionary::FFmpegAVDictionary() : options_(nullptr)
{
}

FFmpegAVDictionary::FFmpegAVDictionary(const FFmpegAVDictionary &other)
{
    options_ = other.clone();
}

FFmpegAVDictionary::~FFmpegAVDictionary()
{
    if (options_)
        av_dict_free(&options_);
}

/**
 * @brief 设置RTSP传输协议
 *
 * @param rtsp_transport RTSP传输协议，例如"tcp"或"udp"
 * @return FFmpegAVDictionary&
 */
FFmpegAVDictionary &FFmpegAVDictionary::setRtspTransport(const std::string &rtsp_transport)
{
    av_dict_set(&options_, "rtsp_transport", rtsp_transport.c_str(), 0);
    return *this;
}

/**
 * @brief 设置缓冲区大小
 *
 * @param buffer_size 缓冲区大小，例如"4096000"
 * @return FFmpegAVDictionary&
 */
FFmpegAVDictionary &FFmpegAVDictionary::setBufferSize(const std::string &buffer_size)
{
    av_dict_set(&options_, "buffer_size", buffer_size.c_str(), 0);
    return *this;
}

/**
 * @brief 设置超时时间
 *
 * @param stimeout 超时时间，例如"5000000"
 * @return FFmpegAVDictionary&
 */
FFmpegAVDictionary &FFmpegAVDictionary::setStimeout(const std::string &stimeout)
{
    av_dict_set(&options_, "stimeout", stimeout.c_str(), 0);
    return *this;
}

/**
 * @brief 设置最大延迟
 *
 * @param max_delay 最大延迟，例如"500000"
 * @return FFmpegAVDictionary&
 */
FFmpegAVDictionary &FFmpegAVDictionary::setMaxDelay(const std::string &max_delay)
{
    av_dict_set(&options_, "max_delay", max_delay.c_str(), 0);
    return *this;
}

/**
 * @brief 克隆AVDictionary
 *
 * @return AVDictionary* 新的AVDictionary指针
 */
AVDictionary *FFmpegAVDictionary::clone() const
{
    AVDictionary *new_options = nullptr;
    if (options_) {
        av_dict_copy(&new_options, options_, 0);
    }
    return new_options;
}
