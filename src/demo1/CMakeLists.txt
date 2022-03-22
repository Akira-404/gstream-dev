cmake_minimum_required(VERSION 3.16)

project(demo1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

# include_directories(/usr/include/gstreamer-1.0/gst)

# add_library(gst_lib /usr/lib/x86_64-linux-gnu/gstreamer-1.0)

add_executable(main main.c)

# target_link_libraries(main PUBLIC gst_lib)
