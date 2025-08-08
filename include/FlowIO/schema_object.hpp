#ifndef FLOWIO_SCHEMA_OBJECT_HPP
#define FLOWIO_SCHEMA_OBJECT_HPP
#include <FlowIO/schema_value_base.hpp>
namespace fio{
    
    template <schema_value ... Layout>
    class schema_object : schema_value_base {
    public:
    private:
        std::tuple<Layout ...> mElems;
    public:
        virtual bool read_from_stream(const binary_stream& stream) {
            int result = 0;
            std::index_sequence_for<Layout...> intSeq;
            (result += std::get<intSeq>(mElems).read_from_stream(stream) == true, ...);
            return result == sizeof...(T);
        }
        template <size_t Idx, schema_value T = std::tuple_element<Idx, std::tuple<Layout...>>::type >
        const T& get() const {
            return mElems.get<Idx>();
        }
        template <size_t Idx, schema_value T = std::tuple_element<Idx, std::tuple<Layout...>>::type >
        void set(const T& value) {
            mElems.get<Idx>() = value;
        }

    private:
    };
}
#endif