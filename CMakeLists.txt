cmake_minimum_required(VERSION 4.0.0)
project(FlowIO)


add_library(FlowIO src/binary_stream.cpp)
set_property(TARGET FlowIO PROPERTY CXX_STANDARD 20)
target_include_directories(FlowIO PUBLIC include)


add_executable(mutable_test test_src/file_stream_test.cpp)
target_link_libraries(mutable_test FlowIO)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(FlowIO PUBLIC FIO_DEBUG=1)
endif()
