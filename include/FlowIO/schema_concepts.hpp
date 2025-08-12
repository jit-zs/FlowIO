#ifndef FLOWIO_SCHEMA_CONCEPTS_HPP
#define FLOWIO_SCHEMA_CONCEPTS_HPP
#include <concepts>
namespace fio {
    class schema_value_base;
    template <typename T>
    concept primitive_value = std::is_integral_v<T> || std::is_floating_point_v<T>;
    enum class endian;
    template <primitive_value T, fio::endian Endian>
    class schema_primitive;

    template <typename T>
    concept integer = std::is_integral_v<T>;

    template <typename T>
    concept schema_value = std::is_base_of_v<schema_value_base, T>;


    template <typename T>
    concept character =
        std::same_as<T, char> ||
        std::same_as<T, signed char> ||
        std::same_as<T, unsigned char> ||
        std::same_as<T, wchar_t> ||
        std::same_as<T, char8_t> ||
        std::same_as<T, char16_t> ||
        std::same_as<T, char32_t>;
}
#endif