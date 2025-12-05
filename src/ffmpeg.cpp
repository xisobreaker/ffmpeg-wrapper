#include "ffmpeg.h"

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

void ffmpeg_network_init()
{
    avformat_network_init();
}

void ffmpeg_log_quiet()
{
    av_log_set_level(AV_LOG_QUIET);
}

std::string ffmpeg_err2str(int errcode)
{
    char errmsg[AV_ERROR_MAX_STRING_SIZE] = {0};
    av_make_error_string(errmsg, AV_ERROR_MAX_STRING_SIZE, errcode);
    return std::string(errmsg);
}
