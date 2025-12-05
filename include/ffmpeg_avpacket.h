#pragma once

extern "C"
{
#include <libavcodec/packet.h>
}

class FFmpegAVPacket
{
public:
    FFmpegAVPacket();
    explicit FFmpegAVPacket(AVPacket *packet);
    ~FFmpegAVPacket();

public:
    AVPacket *packet();
    int       length() const;
    int       streamIndex() const;
    void      unref();

private:
    AVPacket *packet_;
};