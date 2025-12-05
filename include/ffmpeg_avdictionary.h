#pragma once

#include <string>

extern "C"
{
#include <libavutil/dict.h>
}

class FFmpegAVDictionary
{
public:
    FFmpegAVDictionary();
    FFmpegAVDictionary(const FFmpegAVDictionary &other);
    ~FFmpegAVDictionary();

public:
    FFmpegAVDictionary &setRtspTransport(const std::string &rtsp_transport);
    FFmpegAVDictionary &setBufferSize(const std::string &buffer_size);
    FFmpegAVDictionary &setStimeout(const std::string &stimeout);
    FFmpegAVDictionary &setMaxDelay(const std::string &max_delay);

    AVDictionary *clone() const;

private:
    AVDictionary *options_;
};