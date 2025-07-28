cmake_minimum_required(VERSION 4.0.0)
project(FlowIO)


add_library(FlowIO src/FileStream.cpp)
set_property(TARGET FlowIO PROPERTY CXX_STANDARD 20)
target_include_directories(FlowIO PUBLIC include)


add_executable(mutable_test test_src/mutable_test.cpp)
target_link_libraries(mutable_test FlowIO)

