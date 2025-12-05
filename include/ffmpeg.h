#pragma once

#include <string>

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
