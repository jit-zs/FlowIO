#ifndef FLOWIO_EXCEPTION_HPP
#define FLOWIO_EXCEPTION_HPP
#include <stdexcept>
namespace fio {
    enum class io_error_code : char {
        no_space,
        no_access,
    };
    class io_error : std::runtime_error {
    private:
        io_error_code mErrorCode;
    public:
        io_error_code get_error_code() const;
        io_error(const char* what, io_error_code errorCode);
    };
}

#endif