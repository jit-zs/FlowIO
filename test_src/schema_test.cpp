#include <iostream> 
#include <FlowIO/schema_value_base.hpp>

int main() {
    fio::schema_object<
        fio::schema_u64,
        fio::schema_array_u64<fio::schema_i32>
    > obj;
    
}