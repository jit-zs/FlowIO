#ifndef FLOWIO_SCHEMA_VALIDATOR_HPP
#define FLOWIO_SCHEMA_VALIDATOR_HPP

#include <FlowIO/binary_stream.hpp>
namespace fio {
    class schema_validator_base {
    public:
    private:
    public:
        virtual bool read_validate_schema(binary_stream& stream) = 0;
    private:
    };
}

#endif