cmake_minimum_required(VERSION 3.12)
project(FlowIO)

file(GLOB FLOWIO_SRC src/*.cpp)
add_library(FlowIO 
    src/binary_stream.cpp
    src/io_error.cpp)
set_property(TARGET FlowIO PROPERTY CXX_STANDARD 20)
target_include_directories(FlowIO PUBLIC include)


add_executable(mutable_test test_src/file_stream_test.cpp)
set_property(TARGET mutable_test PROPERTY CXX_STANDARD 20)
target_link_libraries(mutable_test PUBLIC FlowIO)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(FlowIO PUBLIC FIO_DEBUG=1)
endif()
