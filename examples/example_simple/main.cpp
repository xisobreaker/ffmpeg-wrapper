#include "ffmpeg_avdictionary.h"
#include "ffmpeg_demuxer.h"
#include "jpeg_frame_sink.h"

#include <glog/logging.h>

int main(int argc, char *argv[])
{
    FFmpegAVDictionary options;
#if 0
    options.setBufferSize("4096000").setRtspTransport("tcp").setStimeout("5000000").setMaxDelay("500000");

    std::string   input_url = "rtsp://127.0.0.1:554/cam/realmonitor/north36";
#else
    std::string input_url = "../../tests/statics/video.mp4";
#endif
    FFmpegDemuxer demuxer(input_url, options);
    demuxer.decodeVideoStream(std::make_shared<JpegFrameSink>(1280, 720));

    int         errcode = 0;
    std::string errmsg;
    for (;;) {
        if (!demuxer.readPacket(errcode, errmsg)) {
            if (errcode == 0) {
                LOG(WARNING) << "ReadPacket: " << errmsg;
            } else if (errcode < 0) {
                LOG(ERROR) << "ReadPacket error: " << errmsg;
            }
            break;
        }
    }
    return 0;
}