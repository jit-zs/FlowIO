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
    bool binary_stream::read_open(const std::filesystem::path& p) {
        return _read_open_file(p.string().c_str());
    }
    bool binary_stream::_write_open_file(const char* path, write_mode mode) {
        mFile = fopen(path, mode == write_mode::append ? "ab+" : "wb+");
        if (mFile) {
            mCurrentAccessMode = access_mode::write;
            return true;
        }
        else {
            return false;
        }
    }
    bool binary_stream::_read_open_file(const char* file) {
        mFile = fopen(file, "r+");
        if (mFile) {
            mCurrentAccessMode = access_mode::read;
            return true;
        }
        else {
            return false;
        }
    }
    binary_stream& binary_stream::write(const void* bytes, size_t count) {
        FIO_ASSERT(mCurrentAccessMode == access_mode::write, "Cannot write to a stream while reading it");
        fwrite(bytes, sizeof(std::byte), count, mFile);
        return *this;
    }
    binary_stream& binary_stream::read(void* bytes, size_t count) {
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