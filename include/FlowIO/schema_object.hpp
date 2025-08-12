#ifndef FLOWIO_SCHEMA_OBJECT_HPP
#define FLOWIO_SCHEMA_OBJECT_HPP
#include <FlowIO/schema_value_base.hpp>
#include <FlowIO/schema_concepts.hpp>
#include <FlowIO/schema_validator_base.hpp>
namespace fio {

    template <schema_value ... Layout>
    class schema_object : public schema_value_base, public schema_validator_base {
    public:
    private:
        std::tuple<Layout ...> mElems;
    public:
        schema_object() = default;
        schema_object(const schema_object& other) = default;
        schema_object(const std::tuple<Layout...>& elems) : mElems(elems) {}
        schema_object& operator=(const schema_object& other) = default;
        ~schema_object() = default;
        /// @brief  Determimnes if a whole file fits this schema
        /// @param stream The file you want to write the bytes to
        /// @return true if the schema matches
        virtual bool read_validate_schema(binary_stream& stream) override {
            bool result = _read_from_stream_impl(stream, std::make_index_sequence<sizeof...(Layout)>{});
            return result && stream.at_last_byte();
        }
        /// @note This function is not for validating the schema of a file
        virtual bool read_from_stream(binary_stream& stream) override {
            return _read_from_stream_impl(stream, std::make_index_sequence<sizeof...(Layout)>{});
        }
        virtual bool write_to_stream(binary_stream& stream) override {
            return _write_to_file_impl(stream, std::make_index_sequence<sizeof...(Layout)>{});
        }
        template <size_t Idx, schema_value T = std::tuple_element<Idx, std::tuple<Layout...>>::type >
        const T& at() const {
            return std::get<Idx>(mElems);
        }
        template <size_t Idx, schema_value T = std::tuple_element<Idx, std::tuple<Layout...>>::type >
        T& at() {
            return std::get<Idx>(mElems);
        }

    private:
        template <size_t ... I>
        bool _read_from_stream_impl(binary_stream& stream, std::integer_sequence<size_t, I...> indexSequence) {
            size_t result = 0;
            ((result += std::get<I>(mElems).read_from_stream(stream) == true), ...);
            return result == indexSequence.size();
        }
        template <size_t ... I>
        bool _write_to_file_impl(binary_stream& stream, std::integer_sequence<size_t, I...> indexSequence) {
            size_t result = 0;
            ((result += std::get<I>(mElems).write_to_stream(stream) == true), ...);
            return result == indexSequence.size();
        }
    };
}
#endif