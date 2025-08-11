#include <iostream> 
#include <FlowIO/schema.hpp>
#include <cstring>

int main() {
    using namespace std::string_literals;
    using file_type = fio::schema_object<
        fio::schema_u64,
        fio::schema_array_u64<fio::schema_object<
        fio::schema_u8,
        fio::schema_null_string
        >>,
        fio::schema_null_string
    >;


    file_type writeObj = file_type();
    writeObj.at<0>() = 33;
    writeObj.at<1>().push_back(std::tuple{ fio::schema_u8(0x2A), fio::schema_null_string("const") });
    writeObj.at<1>().push_back(std::tuple{ fio::schema_u8(0x39), fio::schema_null_string("nair") });
    writeObj.at<2>() = "Fool";

    fio::binary_stream stream;
    stream.write_open("test_dir/schema_test.byte");
    std::cout << "Write: " << writeObj.write_to_stream(stream) << std::endl;;
    stream.close();

    file_type readObj;
    stream.read_open("test_dir/schema_test.byte");
    std::cout << "Read: " << readObj.read_from_stream(stream) << std::endl;
    std::cout << "Test u64: " << (writeObj.at<0>() == readObj.at<0>()) << std::endl;
    std::cout << "Test string: " << (strcmp(writeObj.at<2>().data(), readObj.at<2>().data()) == 0) << std::endl;

    std::cout << "Test u8 1: " << (writeObj.at<1>()[0].at<0>() == readObj.at<1>()[0].at<0>()) << std::endl;
    std::cout << "Test u8 2: " << (writeObj.at<1>()[1].at<0>() == readObj.at<1>()[1].at<0>()) << std::endl;

    std::cout << "Test string 1: " << (strcmp(writeObj.at<1>()[0].at<1>().data(), readObj.at<1>()[0].at<1>().data()) == 0) << std::endl;
    std::cout << "Test string 2: " << (strcmp(writeObj.at<1>()[1].at<1>().data(), readObj.at<1>()[1].at<1>().data()) == 0) << std::endl;
    stream.close();
}