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
        const char* mOpenErr = nullptr;
    public:
        binary_stream(const binary_stream& other) = delete;
        binary_stream();
        ~binary_stream();
        const char* open_error_str() const;
        bool write_open(const std::filesystem::path& file, write_mode mode = write_mode::create);
        bool read_open(const std::filesystem::path& file);
        binary_stream& write(const void* bytes, size_t count);
        binary_stream& read(void* bytes, size_t count);
        void close();

        operator bool() const;
        bool open() const;
    private:
        bool _check_open() const;
        bool _write_open_file(const char* file, write_mode mode);
        bool _read_open_file(const char* file);
    };
}
#endif