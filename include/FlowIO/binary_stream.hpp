#ifndef FLOWIO_FILESTREAM_HPP
#define FLOWIO_FILESTREAM_HPP
#include <stdio.h>
#include <filesystem>

#include <FlowIO/io_error.hpp>
namespace fio {
    enum class write_mode {
        append,
        create
    };
    class binary_stream {
    public:
    private:
        enum class access_mode{
            read,
            write,
            none
        }mCurrentAccessMode = access_mode::none;
        FILE* mFile = nullptr;
    public:
        binary_stream(const binary_stream& other) = delete;
        binary_stream();
        ~binary_stream();

        bool write_open(const std::filesystem::path& file, write_mode mode = write_mode::create);
        binary_stream& write(const std::byte* bytes, size_t count);
        binary_stream& read(std::byte* bytes, size_t count);
        void close();
    private:
        bool _write_open_file(const char* file, write_mode mode);
    };
}
#endif