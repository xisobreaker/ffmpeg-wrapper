project(example_simple)

add_executable(${PROJECT_NAME} main.cpp jpeg_frame_sink.cpp)

target_link_libraries(${PROJECT_NAME} ffmpegcpp)

target_link_libraries(${PROJECT_NAME} 
    avcodec
    avdevice 
    avfilter 
    avformat 
    avutil 
    swscale
)