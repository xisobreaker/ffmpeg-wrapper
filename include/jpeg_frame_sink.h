#pragma once

#include "ffmpeg_avframe.h"
#include "ffmpeg_frame_sink.h"

#include <atomic>
#include <functional>
#include <memory>
#include <opencv2/opencv.hpp>

extern "C"
{
#include <libswscale/swscale.h>
}

class JpegFrameSink : public FFmpegFrameSink
{
    using FrameCallback = std::function<void(int64_t, uint32_t, int, int, cv::Mat &)>;

public:
    JpegFrameSink(int width, int height, FrameCallback frame_callback);
    ~JpegFrameSink();

public:
    /**
     * @brief 设置解码器参数
     *
     * @param codecpar
     */
    void setCodecpar(const AVCodecParameters *codecpar) override;

    /**
     * @brief 帧数据处理
     *
     * @param frame
     * @param timestamp
     */
    void handleFrame(const FFmpegAVFrame *frame, int64_t timestamp) override;

private:
    std::atomic<uint32_t>          next_frame_id_; // 字增长帧ID
    std::shared_ptr<FFmpegAVFrame> bgr_frame_;
    int                            bgr_buffer_size_;
    SwsContext                    *img_convert_ctx_;
    FrameCallback                  frame_callback_;
};
