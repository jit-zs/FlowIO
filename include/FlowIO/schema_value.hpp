#ifndef FLOWIO_SCHEMA_VALUE_HPP
#define FLOWIO_SCHEMA_VALUE_HPP
#include <stdint.h>
#include <type_traits>

#include <FlowIO/binary_stream.hpp>
namespace fio {
    class schema_value {
    public:
    private:
    public:
        virtual bool read_from_stream(const binary_stream& stream) = 0;
    private:
    };
    template <typename T>
    concept primitive_value = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <primitive_value T>
    class schema_primitive : schema_value {
    public:
    private:
        T mValue;
    public:
        virtual bool read_from_stream(const binary_stream& stream) override{
            try{
                stream.read(&mValue, sizeof(T));
            }
            catch(fio::io_error& err){  
                return false;
            }
            return true;
        }
        T get() const {
            return mValue;
        }
        void set(T value) {
            mValue = value;
        }
    private:
    };
    typedef schema_primitive<uint64_t> schema_uint8;
    typedef schema_primitive<uint64_t> schema_uint16;
    typedef schema_primitive<uint64_t> schema_uint32;
    typedef schema_primitive<uint64_t> schema_uint64;

    typedef schema_primitive<uint64_t> schema_int8;
    typedef schema_primitive<uint64_t> schema_int16;
    typedef schema_primitive<uint64_t> schema_int32;
    typedef schema_primitive<uint64_t> schema_int64;

    typedef schema_primitive<float> schema_float;
    typedef schema_primitive<double> schema_double;


}

#endif