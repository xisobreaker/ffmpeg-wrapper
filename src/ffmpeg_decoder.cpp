#include "ffmpeg_decoder.h"

#include <glog/logging.h>
#include <stdexcept>

FFmpegDecoder::FFmpegDecoder(const AVCodecParameters *codecpar)
{
    const AVCodec *codec = avcodec_find_decoder(codecpar->codec_id);
    if (!codec) {
        throw std::runtime_error("Can't find codec for stream " + std::string(av_get_media_type_string(codecpar->codec_type)));
    }
    stream_ctx_ = avcodec_alloc_context3(codec);
    if (!stream_ctx_) {
        throw std::runtime_error("Can't alloc codec context for stream " + std::string(codec->name));
    }

    if (avcodec_parameters_to_context(stream_ctx_, codecpar) != 0) {
        throw std::runtime_error("Can't copy " + std::string(codec->name) + " decoder context!");
    }
    if (avcodec_open2(stream_ctx_, codec, NULL) < 0) {
        throw std::runtime_error("Can't open coedc " + std::string(codec->name));
    }
}

FFmpegDecoder::~FFmpegDecoder()
{
    if (stream_ctx_) {
        avcodec_free_context(&stream_ctx_);
    }
}

void FFmpegDecoder::decode(FFmpegAVPacket *pkt, FFmpegFrameSink *sink)
{
    int ret = avcodec_send_packet(stream_ctx_, pkt->packet());
    if (ret < 0) {
        throw std::runtime_error("Error submitting the packet to the decoder!");
    }

    while (ret >= 0) {
        ret = avcodec_receive_frame(stream_ctx_, frame_.frame());
        if (ret == AVERROR_EOF || ret == AVERROR(EAGAIN)) {
            return;
        } else if (ret < 0) {
            throw std::runtime_error("Error during decoding!");
        }

        if (!frame_.frame()->sample_aspect_ratio.num) {
            frame_.frame()->sample_aspect_ratio = stream_ctx_->sample_aspect_ratio;
        }

        // 处理解码后的帧数据
        sink->handleFrame(&frame_);
        frame_.unref();
    }
}