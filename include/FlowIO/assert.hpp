#ifndef FLOWIO_ASSERT_HPP
#define FLOWIO_ASSERT_HPP
#include <iostream>

#if FIO_DEBUG
#define FIO_ASSERT(condition, message)\
    do\
        if (!(condition)){\
            std::cerr << "Assertion '" << #condition << "' failed in '" << __FILE__\
                << "' line " << __LINE__ << ": " << message << std::endl;\
                std::set_terminate(std::terminate_handler([](){}));\
            std::terminate();\
        }\
    while(false);
#else 
#define FIO_ASSERT(condition, message) void()
#endif
#endif