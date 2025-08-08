#ifndef FLOWIO_SCHEMA_CONCEPTS_HPP
#define FLOWIO_SCHEMA_CONCEPTS_HPP
#include <concepts>
namespace fio {
    class schema_value_base;
    template <typename T>
    concept primitive_value = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <typename T>
    concept integer = std::is_integral_v<T>;

    template <typename T>
    concept schema_value = std::is_base_of_v<schema_value_base, T>;
}
#endif