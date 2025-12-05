#include "jpeg_frame_sink.h"

#include <glog/logging.h>

JpegFrameSink::JpegFrameSink()
{
}

JpegFrameSink::~JpegFrameSink()
{
}

void JpegFrameSink::handleFrame(const FFmpegAVFrame *frame)
{
    LOG(INFO) << "JpegFrameSink::handleFrame";
}