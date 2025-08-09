#ifndef FLOWIO_SCHEMA_VALUE_HPP
#define FLOWIO_SCHEMA_VALUE_HPP
#include <stdint.h>
#include <type_traits>
#include <map>

#include <FlowIO/binary_stream.hpp>
namespace fio {



    class schema_value_base {
    public:
    private:
    public:
        virtual ~schema_value_base() = default;
        virtual bool read_from_stream(binary_stream& stream) = 0;
        virtual bool write_to_stream(binary_stream& stream) = 0;
    private:
    };






}

#endif