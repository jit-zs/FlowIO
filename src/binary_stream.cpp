#include <FlowIO/binary_stream.hpp>
#include <FlowIO/assert.hpp>
#include <stdexcept>
#include <string>
#include <fcntl.h>
#include <stdio.h>

namespace fio {
    binary_stream::binary_stream() {

    }
    binary_stream::~binary_stream() {

    }
    bool binary_stream::write_open(const std::filesystem::path& p, write_mode mode) {
        return _write_open_file(p.string().c_str(), mode);
    }
    bool binary_stream::_write_open_file(const char* path, write_mode mode) {
        mFile = fopen(path, mode == write_mode::append ? "ab+" : "wb+");
        return mFile != nullptr;
    }
    binary_stream& binary_stream::write(const std::byte* bytes, size_t count) {
        FIO_ASSERT(mCurrentAccessMode == access_mode::read, "Cannot write to a stream while reading it");
        fwrite(bytes, sizeof(std::byte), count, mFile);
        return *this;
    }
    binary_stream& binary_stream::read(std::byte* bytes, size_t count) {
        FIO_ASSERT(mCurrentAccessMode == access_mode::read, "Cannot read from a stream while writing to it");
        fread(bytes, sizeof(std::byte), count, mFile);
        return *this;
    }

    void binary_stream::close() {
        FIO_ASSERT(mFile, "The stream is not open and has nothing to close");
        fclose(mFile); 
        mFile = nullptr;
        mCurrentAccessMode = access_mode::none;
    }
}