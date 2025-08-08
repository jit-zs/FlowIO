#ifndef FLOWIO_SCHEMA_ARRAY_HPP
#define FLOWIO_SCHEMA_ARRAY_HPP
#include <FlowIO/schema_value_base.hpp>
#include <FlowIO/schema_concepts.hpp>
namespace fio{
        template <integer LengthType, schema_value EntryLayout>
    class schema_array : schema_value_base {
    public:
    private:
        LengthType mLength = 0;
        EntryLayout* mData = nullptr;
    public:
        virtual bool read_from_stream(const binary_stream& stream) override {
            stream.read(&mLength, sizeof(mLength));
        }

    private:
    };

    template <schema_value T>
    using schema_array_u8 = schema_array<uint8_t, T>;
    template <schema_value T>
    using schema_array_u16 = schema_array<uint16_t, T>;
    template <schema_value T>
    using schema_array_u32 = schema_array<uint32_t, T>;
    template <schema_value T>
    using schema_array_u64 = schema_array<uint64_t, T>;

    template <schema_value T>
    using schema_array_i8 = schema_array<int8_t, T>;
    template <schema_value T>
    using schema_array_i16 = schema_array<int16_t, T>;
    template <schema_value T>
    using schema_array_i32 = schema_array<int32_t, T>;
    template <schema_value T>
    using schema_array_i64 = schema_array<int64_t, T>;
}

#endif