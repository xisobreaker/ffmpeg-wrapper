#include "ffmpeg_avpacket.h"

#include <stdexcept>

FFmpegAVPacket::FFmpegAVPacket() : packet_(av_packet_alloc())
{
    if (!packet_) {
        throw std::runtime_error("Can't create AVPacket!");
    }
}

FFmpegAVPacket::FFmpegAVPacket(AVPacket *packet) : packet_(packet)
{
}

FFmpegAVPacket::~FFmpegAVPacket()
{
    if (packet_)
        av_packet_free(&packet_);
}

AVPacket *FFmpegAVPacket::packet()
{
    return packet_;
}

int FFmpegAVPacket::length() const
{
    return packet_->size;
}

int FFmpegAVPacket::streamIndex() const
{
    return packet_->stream_index;
}

void FFmpegAVPacket::unref()
{
    av_packet_unref(packet_);
}
