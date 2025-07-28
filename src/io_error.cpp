#include <FlowIO/io_error.hpp>

namespace fio {
    io_error::io_error(const char* what, io_error_code errorCode) : std::runtime_error(what) {
        mErrorCode = errorCode;
    }
}