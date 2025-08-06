cmake_minimum_required(VERSION 3.12)
project(FlowIO)
set(CMAKE_CXX_STANDARD 20)


add_library(FlowIO 
    src/binary_stream.cpp
    src/io_error.cpp
    )
target_include_directories(FlowIO PUBLIC include)


add_executable(file_stream_test test_src/file_stream_test.cpp)
target_link_libraries(file_stream_test PUBLIC FlowIO)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(FlowIO PUBLIC FIO_DEBUG=1)
endif()
