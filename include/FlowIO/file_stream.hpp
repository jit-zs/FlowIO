#ifndef FLOWIO_FILESTREAM_HPP
#define FLOWIO_FILESTREAM_HPP
#include <stdio.h>
namespace fio {
    class file_stream {
    public:
    private:
        FILE* mFile = nullptr;
    public:
    file_stream(const file_stream& other) = delete;
    file_stream();
    ~file_stream();

    
    private:
    };
}
#endif