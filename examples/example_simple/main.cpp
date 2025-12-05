#include "ffmpeg_avdictionary.h"
#include "ffmpeg_demuxer.h"
#include "jpeg_frame_sink.h"

#include <glog/logging.h>

int main(int argc, char *argv[])
{
    FFmpegAVDictionary options;
    options.setBufferSize("4096000").setRtspTransport("tcp").setStimeout("5000000").setMaxDelay("500000");

    std::string   input_url = "rtsp://127.0.0.1:554/cam/realmonitor/north36";
    FFmpegDemuxer demuxer(input_url, options);
    demuxer.decodeVideoStream(std::make_shared<JpegFrameSink>());

    int         errcode = 0;
    std::string errmsg;
    for (;;) {
        if (!demuxer.readPacket(errcode, errmsg)) {
            LOG(ERROR) << "error: " << errmsg;
            if (errcode <= 0)
                break;
        }
    }
    return 0;
}