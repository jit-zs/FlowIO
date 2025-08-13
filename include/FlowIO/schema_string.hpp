#ifndef FLOWIO_SCHEMA_STRING_HPP
#define FLOWIO_SCHEMA_STRING_HPP
#include <FlowIO/schema_value_base.hpp>
#include <FlowIO/schema_concepts.hpp>
#include <FlowIO/assert.hpp>
#include <FlowIO/endian.hpp>
#include <FlowIO/byteswap.hpp>
#include <stdint.h>
#include <string>
namespace fio {
    template <character T, fio::endian Endian>
    class basic_schema_null_string : public schema_value_base {
    public:
        using std_library_type = std::basic_string<T, std::char_traits<T>, std::allocator<char>>;
    private:
        T* mData = nullptr;
        size_t mCapacity = 0;
        size_t mLength = 0;
    public:
        basic_schema_null_string() {
            mCapacity = 1;
            mLength = 0;
            mData = new T[mCapacity];
            mData[0] = 0;
        }
        basic_schema_null_string(const basic_schema_null_string& other) {
            _copy_string(other.length(), other.capacity(), other.data());
        }
        basic_schema_null_string(const std_library_type& other) {
            _copy_string(other.length(), other.capacity(), other.data());
        }
        basic_schema_null_string& operator=(const std_library_type& other) {
            _copy_string(other.length(), other.capacity(), other.data());
            return *this;
        }
        basic_schema_null_string& operator=(const basic_schema_null_string& other) {
            _copy_string(other.length(), other.capacity(), other.data());
            return *this;
        }
        ~basic_schema_null_string() {
            delete[] mData;
        }
        void push_back(T char_) {
            _ensure_capacity(mLength + 1);
            mData[mLength++] = char_;
        }
        T pop_back() {
            return mData[--mLength];
        }
        T& at(size_t idx) {
            FIO_ASSERT(idx < mLength, "Out of index range error");
            return mData[idx];
        }
        const T& at(size_t idx) const {
            FIO_ASSERT(idx < mLength, "Out of index range error");
            return mData[idx];
        }
        size_t length() const {
            return mLength;
        }
        size_t size() const {
            return mLength;
        }
        size_t capacity() const {
            return mCapacity;
        }

        operator std::string() const {
            return mData;
        }
        T* begin() const {
            return mData;
        }
        T* end() const {
            return mData + mLength;
        }
        const T* data() const {
            return mData;
        }
        void clear() {
            if (mData)
                delete[] mData;
            mData = new T[1];
            mCapacity = 1;
            mLength = 0;
        }
        virtual bool write_to_stream(binary_stream& stream) {
            T* c = mData;
            size_t result = 0;
            try {
                for (size_t i = 0; i < mLength + 1;i++) {
                    T placeholder = c[i];
                    if constexpr (sizeof(T) > 1 && Endian != fio::endian::none)
                        if (get_platform_endian() != Endian)
                            placeholder = byteswap(placeholder);
                    if (stream.write(&placeholder, sizeof(T)) == true)
                        result++;
                }
            }
            catch (fio::io_error& err) {
                return false;
            }



            return result == mLength + 1;
        }
        virtual bool read_from_stream(binary_stream& stream) {
            clear();
            T c;
            size_t result;
            bool streamState = true;
            try {
                while (streamState = stream.read(&c, sizeof(T))) {
                    result++;
                    if constexpr (sizeof(T) > 1 && Endian != fio::endian::none)
                        if (get_platform_endian() != Endian)
                            c = byteswap(c);
                    push_back(c);
                    if (c == 0)
                        break;
                }
            }
            catch (fio::io_error& err) {
                return false;
            }

            return streamState;
        }
    private:
        void _copy_string(size_t len, size_t cap, const T* data) {
            if (mData)
                delete[] mData;
            if (data == nullptr) {
                mData = new T[1];
                mData[0] = 0;
                return;
            }
            mLength = len;
            mCapacity = cap;
            mData = new T[cap];
            const T* c = data;
            for (size_t i = 0; ; i++) {
                mData[i] = data[i];
                if (data[i] == 0)
                    break;
            }
        }
        void _ensure_capacity(size_t desiredCapacity) {
            if (mCapacity < desiredCapacity) {
                mCapacity *= 2;
                T* temp = new T[mCapacity];
                std::copy(begin(), end(), temp);
                delete[] mData;
                mData = temp;
            }
        }
    };

    typedef basic_schema_null_string<char, fio::endian::none> schema_null_string;
    typedef basic_schema_null_string<char8_t, fio::endian::none> schema_null_string_c8;
    typedef basic_schema_null_string<unsigned char, fio::endian::none> schema_null_string_u8;
    typedef basic_schema_null_string<signed char, fio::endian::none> schema_null_string_i8;

    

    typedef basic_schema_null_string<wchar_t, fio::endian::little> schema_null_wstringl;
    typedef basic_schema_null_string<char16_t, fio::endian::little> schema_null_string_c16l;
    typedef basic_schema_null_string<char32_t, fio::endian::little> schema_null_string_c32l;

    typedef basic_schema_null_string<wchar_t, fio::endian::big> schema_null_wstringb;
    typedef basic_schema_null_string<char16_t, fio::endian::big> schema_null_string_c16b;
    typedef basic_schema_null_string<char32_t, fio::endian::big> schema_null_string_c32b;
}
#endif