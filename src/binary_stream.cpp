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
        if (mFile) {
            fclose(mFile);
            mFile = nullptr;
        }
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
            mLastErr = strerror(errno);
            return false;
        }
    }

    binary_stream& binary_stream::write(const void* bytes, size_t count) {
        FIO_ASSERT(mCurrentAccessMode == access_mode::write, "Cannot write to a stream while reading it");
        fwrite(bytes, sizeof(std::byte), count, mFile);
        if (int err = ferror(mFile)) {
            _raise_error(strerror(errno));
        }

        return *this;
    }
    binary_stream& binary_stream::read(void* bytes, size_t count) {
        FIO_ASSERT(mCurrentAccessMode == access_mode::read, "Cannot read from a stream while writing to it");
        size_t currFilePtr = ftell(mFile);
        fseek(mFile, 0L, SEEK_END);
        size_t filesize = ftell(mFile);
        fseek(mFile, currFilePtr, SEEK_SET);

        if (currFilePtr + count - 1 >= filesize) {
            _raise_error("Error trying to read past EOF");
        }
        fread(bytes, sizeof(std::byte), count, mFile);
        if (ferror(mFile)) {
            _raise_error(strerror(errno));
        }

        return *this;
    }
    binary_stream::operator bool() const {
        return _check_open();
    }
    bool binary_stream::is_open() const {
        return _check_open();
    }
    void binary_stream::close() {
        if (!mFile) {
            return;
        }
        if (fclose(mFile)) {
            mFile = nullptr;
            mCurrentAccessMode = access_mode::none;
            _raise_error("The file could not be finalized");
        }
        mFile = nullptr;
        mCurrentAccessMode = access_mode::none;
    }
    bool binary_stream::_check_open() const {
        return mFile;
    }
    const char* binary_stream::open_error_str() const {
        return mLastErr;
    }

    void binary_stream::_raise_error(const char* errorMsg) {
        mLastErr = errorMsg;
        throw fio::io_error(mLastErr);
    }
}