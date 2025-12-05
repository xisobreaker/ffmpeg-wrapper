#include "ffmpeg_demuxer.h"

#include "ffmpeg.h"

#include <glog/logging.h>
#include <libavformat/avformat.h>
#include <stdexcept>

FFmpegDemuxer::FFmpegDemuxer(const std::string &input_url, const FFmpegAVDictionary &options) :
    input_url_(input_url), options_(options), packet_(std::make_shared<FFmpegAVPacket>())
{
    AVDictionary *new_opts = options_.clone();

    // 申请AVFormatContext类型变量并初始化默认参数
    if (!(format_ctx_ = avformat_alloc_context())) {
        throw std::runtime_error("Can't create AVFormatContext for input stream!");
    }

    // 打开输入流
    int errcode = avformat_open_input(&format_ctx_, input_url_.c_str(), nullptr, &new_opts);
    if (errcode != 0) {
        throw std::runtime_error("avformat_open_input failed" + ffmpeg_err2str(errcode));
    }

    // 查找流信息
    if ((errcode = avformat_find_stream_info(format_ctx_, nullptr)) < 0) {
        throw std::runtime_error("Can't find stream info: " + ffmpeg_err2str(errcode));
    }

    // 创建输入流对象
    for (int i = 0; i < format_ctx_->nb_streams; i++) {
        input_streams_.emplace_back(format_ctx_, format_ctx_->streams[i]);
    }
}

FFmpegDemuxer::~FFmpegDemuxer()
{
    if (format_ctx_)
        avformat_close_input(&format_ctx_);
}

bool FFmpegDemuxer::readPacket(int &errcode, std::string &errmsg)
{
    int ret = av_read_frame(format_ctx_, packet_->packet());
    if (ret < 0) {
        errmsg = ffmpeg_err2str(ret);

        if (ret == AVERROR_EOF) {
            errcode = 0;
        } else if (ret == AVERROR(EAGAIN)) {
            errcode = 1;
        } else {
            errcode = ret;
        }
        return false;
    }

    // 解码该包
    int stream_index = packet_->streamIndex();
    if (stream_index >= 0 && stream_index < input_streams_.size()) {
        input_streams_[stream_index].decodePacket(packet_.get());
    }
    packet_->unref();
    return true;
}

void FFmpegDemuxer::decodeVideoStream(const std::shared_ptr<FFmpegFrameSink> &sink)
{
    int stream_index = av_find_best_stream(format_ctx_, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (stream_index < 0) {
        throw std::runtime_error("Can't find video stream, " + ffmpeg_err2str(stream_index));
    }

    if (stream_index >= input_streams_.size()) {
        throw std::runtime_error("Video stream index out of range!");
    }
    input_streams_[stream_index].setFrameSink(sink);
}