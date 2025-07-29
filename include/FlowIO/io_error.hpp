#ifndef FLOWIO_EXCEPTION_HPP
#define FLOWIO_EXCEPTION_HPP
#include <stdexcept>
namespace fio {
    class io_error : std::runtime_error {
    private:
    public:
        io_error(const char* what);
    };
}

#endif