#include <iostream> 
#include <FlowIO/schema.hpp>

int main() {
    using file_type = fio::schema_object<
        fio::schema_u64,
        fio::schema_array_u64<fio::schema_u8>
        > ;
    
    file_type obj = file_type();
    obj.at<0>() = 33;
    obj.at<1>().push_back(0xFF);
    obj.at<1>().push_back(0xAF);
    fio::binary_stream stream;
    stream.write_open("test_dir/schema_test.byte");
    std::cout << "Write:" << obj.write_to_stream(stream) << std::endl;;
    stream.close();
}