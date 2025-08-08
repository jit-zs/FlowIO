#ifndef FLOWIO_SCHEMA_PRIMITIVE_HPP 
#define FLOWIO_SCHEMA_PRIMITIVE_HPP
#include <FlowIO/schema_value_base.hpp>
#include <FlowIO/schema_concepts.hpp>
namespace fio{
      template <primitive_value T>
    class schema_primitive : schema_value_base {
    public:
    private:
        T mValue;
    public:
        virtual bool read_from_stream(const binary_stream& stream) override {
            try {
                stream.read(&mValue, sizeof(T));
            }
            catch (fio::io_error& err) {
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
    typedef schema_primitive<uint64_t> schema_u8;
    typedef schema_primitive<uint64_t> schema_u16;
    typedef schema_primitive<uint64_t> schema_u32;
    typedef schema_primitive<uint64_t> schema_u64;

    typedef schema_primitive<uint64_t> schema_i8;
    typedef schema_primitive<uint64_t> schema_i16;
    typedef schema_primitive<uint64_t> schema_i32;
    typedef schema_primitive<uint64_t> schema_i64;

    typedef schema_primitive<float> schema_float;
    typedef schema_primitive<double> schema_double;



}

#endif