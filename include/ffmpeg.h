#pragma once

#include <string>

extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/dict.h>
}

struct AVDictionaryDeleter {
    void operator()(AVDictionary *dict) const
    {
        if (dict) {
            av_dict_free(&dict);
        }
    }
};

struct AVFormatContextDeleter {
    void operator()(AVFormatContext *ctx) const
    {
        if (ctx) {
            avformat_close_input(&ctx);
        }
    }
};

/**
 * @brief avformat network init
 *
 */
void ffmpeg_network_init();

/**
 * @brief disable ffmpeg log
 *
 */
void ffmpeg_log_quiet();

/**
 * @brief convert ffmpeg error code to string
 *
 * @param errcode ffmpeg error code
 * @return std::string error message
 */
std::string ffmpeg_err2str(int errcode);
