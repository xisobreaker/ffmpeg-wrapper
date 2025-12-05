#pragma once

#include "ffmpeg_avdictionary.h"
#include "ffmpeg_avpacket.h"
#include "ffmpeg_avstream.h"

#include <memory>
#include <vector>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavformat/avformat.h>
#include <libavutil/adler32.h>
#include <libavutil/avutil.h>
#include <libavutil/frame.h>
#include <libavutil/imgutils.h>
#include <libavutil/timestamp.h>
#include <libswscale/swscale.h>
}

#include <string>

class FFmpegDemuxer
{
public:
    FFmpegDemuxer(const std::string &input_url, const FFmpegAVDictionary &options);
    ~FFmpegDemuxer();

public:
    bool readPacket(int &errcode, std::string &errmsg);
    void decodeVideoStream(const std::shared_ptr<FFmpegFrameSink> &sink);

    const std::vector<FFmpegAVStream> &inputStreams() const
    {
        return input_streams_;
    }

private:
    std::string                     input_url_;
    FFmpegAVDictionary              options_;
    AVFormatContext                *format_ctx_;
    std::shared_ptr<FFmpegAVPacket> packet_;
    std::vector<FFmpegAVStream>     input_streams_;
};