#ifndef FLOWIO_SCHEMA_ARRAY_HPP
#define FLOWIO_SCHEMA_ARRAY_HPP
#include <FlowIO/schema_value_base.hpp>
#include <FlowIO/schema_concepts.hpp>
#include <FlowIO/assert.hpp>
namespace fio {
    template <integer LengthType, schema_value EntryLayout>
    class schema_array : public schema_value_base {
    public:
    private:
        LengthType mLength = 0;
        LengthType mCapacity = 0;
        EntryLayout* mData = nullptr;

    public:
        schema_array() {
            mData = new EntryLayout[1];
            mCapacity = 1;
            mLength = 0;
        }
        schema_array(const schema_array& other) {
            if (mData)
                delete[] mData;
            mData = new EntryLayout[other.mCapacity];
            mCapacity = other.mCapacity;
            mLength = other.mLength;

            std::copy(other.mData, other.mData + other.mLength, mData);
        }
        schema_array& operator=(const schema_array& other) {
            if (mData)
                delete[] mData;
            mData = new EntryLayout[other.mCapacity];
            mCapacity = other.mCapacity;
            mLength = other.mLength;

            std::copy(other.mData, other.mData + other.mLength, mData);
        }
        virtual ~schema_array() {
            delete[] mData;
        }
        EntryLayout& operator[](LengthType idx) {
            FIO_ASSERT(idx < mLength, "Out of bounds error");
            return mData[idx];
        }
        const EntryLayout& operator[](LengthType idx) const {
            FIO_ASSERT(idx < mLength, "Out of bounds error");
            return mData[idx];
        }
        void push_back(const EntryLayout& item) {
            _ensure_capacity(mLength + 1);
            mData[mLength] = item;
            mLength++;
        }
        EntryLayout pop_back() {
            FIO_ASSERT(mLength > 0, "Cannot remove an element from an empty vector");
            return mData[--mLength];
        }

        EntryLayout* begin() const {
            return mData;
        }
        EntryLayout* end() const {
            return mData + mLength;
        }

        LengthType length() const {
            return mLength;
        }
        LengthType capacity() const {
            return mCapacity;
        }
        EntryLayout at(LengthType idx) {
            FIO_ASSERT(idx < mLength, "Out of bounds error");
            return mData[idx];
        }
        void clear() {
            mLength = 0;
            mCapacity = 1;
            if (mData)
                delete[] mData;
            mData = new EntryLayout[mCapacity];
        }
        void resize(LengthType size) {
            _ensure_capacity(size);
            mLength = size;
        }
        bool read_from_stream(binary_stream& stream) override {
            clear();
            try {
                stream.read(&mLength, sizeof(mLength));
            }
            catch (fio::io_error& err) {
                return false;
            }

            resize(mLength);
            LengthType result = 0;
            for (LengthType i = 0; i < mLength; i++) {
                if (mData[i].read_from_stream(stream) == true)
                    result++;
            }
            return result == mLength;
        }
        bool write_to_stream(binary_stream& stream) override {
            try {
                stream.write(&mLength, sizeof(mLength));
            }
            catch (fio::io_error& err) {
                return false;
            }
            LengthType result = 0;
            for (LengthType i = 0; i < mLength; i++) {
                if (mData[i].write_to_stream(stream) == true)
                    result++;
            }
            return result == mLength;
        }
    private:
        void _ensure_capacity(LengthType desiredCapacity) {
            if (desiredCapacity > mCapacity) {
                EntryLayout* temp = new EntryLayout[mCapacity * 2];
                std::copy(mData, mData + mLength, temp);
                delete[] mData;
                mData = temp;
                mCapacity *= 2;
            }
        }
        void _copy_array(LengthType len, LengthType cap, EntryLayout data) {
            FIO_ASSERT(data != mData, "Data cannot copy a itself");
            if (mData)
                delete[] mData;
            mData = new EntryLayout[cap];
            mCapacity = cap;
            mLength = len;
            std::copy(data, data + len, mData);
        }
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