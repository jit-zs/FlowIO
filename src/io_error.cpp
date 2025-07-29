#include <FlowIO/io_error.hpp>

namespace fio {
    io_error::io_error(const char* what) : std::runtime_error(what) {

    }
}