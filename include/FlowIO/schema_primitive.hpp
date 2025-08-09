#ifndef FLOWIO_SCHEMA_PRIMITIVE_HPP 
#define FLOWIO_SCHEMA_PRIMITIVE_HPP
#include <FlowIO/schema_value_base.hpp>
#include <FlowIO/schema_concepts.hpp>
namespace fio {
    template <primitive_value T>
    class schema_primitive final : public schema_value_base {
    public:
    private:
        T mValue;
    public:
        schema_primitive() = default;
        schema_primitive(const schema_primitive& other) = default;
        schema_primitive& operator=(const schema_primitive& other) = default;
        schema_primitive(T value) : mValue(value){}
        ~schema_primitive() = default;
        virtual bool read_from_stream(binary_stream& stream) override {
            try {
                stream.read(&mValue, sizeof(mValue));
            }
            catch (fio::io_error& err) {
                return false;
            }
            return true;
        }
        virtual bool write_to_stream(binary_stream& stream) override {
            try {
                stream.write(&mValue, sizeof(mValue));
            }
            catch (fio::io_error& err) {
                return false;
            }
            return true;
        }
        operator T() const {
            return mValue;
        }
        schema_primitive& operator=(T value) {
            mValue = value;
            return *this;
        }
    private:
    };
    typedef schema_primitive<uint8_t> schema_u8;
    typedef schema_primitive<uint16_t> schema_u16;
    typedef schema_primitive<uint32_t> schema_u32;
    typedef schema_primitive<uint64_t> schema_u64;

    typedef schema_primitive<int8_t> schema_i8;
    typedef schema_primitive<int16_t> schema_i16;
    typedef schema_primitive<int32_t> schema_i32;
    typedef schema_primitive<int64_t> schema_i64;

    typedef schema_primitive<float> schema_float;
    typedef schema_primitive<double> schema_double;



}

#endif