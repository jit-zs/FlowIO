#ifndef FLOWIO_SCHEMA_PRIMITIVE_HPP 
#define FLOWIO_SCHEMA_PRIMITIVE_HPP
#include <FlowIO/schema_value_base.hpp>
#include <FlowIO/schema_concepts.hpp>
#include <FlowIO/byteswap.hpp>
#include <FlowIO/endian.hpp>
namespace fio {
    template <primitive_value T, fio::endian Endian>
    class schema_primitive final : public schema_value_base {
    public:
        using value_type = T;
    private:
        T mValue;
    public:
        schema_primitive() = default;
        schema_primitive(const schema_primitive& other) = default;
        schema_primitive& operator=(const schema_primitive& other) = default;
        schema_primitive(T value) : mValue(value) {}
        ~schema_primitive() = default;
        virtual bool read_from_stream(binary_stream& stream) override {
            try {
                stream.read(&mValue, sizeof(mValue));
                if constexpr (sizeof(T) > 1 && Endian != fio::endian::none)
                    if (get_platform_endian() != Endian)
                        mValue = byteswap(mValue);
            }
            catch (fio::io_error& err) {
                return false;
            }
            return true;
        }
        virtual bool write_to_stream(binary_stream& stream) override {
            try {
                T placeholder = mValue;
                if constexpr (sizeof(T) && Endian != fio::endian::none)
                    if (get_platform_endian() != Endian) {
                        placeholder = byteswap(placeholder);
                    }
                stream.write(&placeholder, sizeof(T));
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
    typedef schema_primitive<uint8_t, fio::endian::none> schema_u8;
    typedef schema_primitive<int8_t, fio::endian::none> schema_i8;

    typedef schema_primitive<uint16_t, fio::endian::little> schema_u16l;
    typedef schema_primitive<uint32_t, fio::endian::little> schema_u32l;
    typedef schema_primitive<uint64_t, fio::endian::little> schema_u64l;

    typedef schema_primitive<int16_t, fio::endian::little> schema_i16l;
    typedef schema_primitive<int32_t, fio::endian::little> schema_i32l;
    typedef schema_primitive<int64_t, fio::endian::little> schema_i64l;

    typedef schema_primitive<float, fio::endian::little> schema_floatl;
    typedef schema_primitive<double, fio::endian::little> schema_doublel;


    typedef schema_primitive<uint16_t, fio::endian::big> schema_u16b;
    typedef schema_primitive<uint32_t, fio::endian::big> schema_u32b;
    typedef schema_primitive<uint64_t, fio::endian::big> schema_u64b;

    typedef schema_primitive<int16_t, fio::endian::big> schema_i16b;
    typedef schema_primitive<int32_t, fio::endian::big> schema_i32b;
    typedef schema_primitive<int64_t, fio::endian::big> schema_i64b;

    typedef schema_primitive<float, fio::endian::big> schema_floatb;
    typedef schema_primitive<double, fio::endian::big> schema_doubleb;


}

#endif