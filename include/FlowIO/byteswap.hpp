#ifndef FIO_BYTESWAP_HPP
#define FIO_BYTESWAP_HPP
#include <concepts>
#include <tuple>
namespace fio {
    template <typename T>
    concept byteswappable = std::integral<T> || std::floating_point<T>;
    template <byteswappable T>
    T byteswap(T val) {
        if constexpr (sizeof(T) == 1) return val; 
       
        char* bytes = reinterpret_cast<char*>(&val);
        char finalBytes[sizeof(T)] = {};
        for (size_t i = 0; i < sizeof(T); i++) {
            finalBytes[sizeof(T) - (i + 1)] = bytes[i];
        }

        return *reinterpret_cast<T*>(finalBytes);
    }
}
#endif