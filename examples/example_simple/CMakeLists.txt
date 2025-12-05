project(example_simple)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} avkit)

target_link_libraries(${PROJECT_NAME} 
    avcodec
    avdevice 
    avfilter 
    avformat 
    avutil 
    swscale
)