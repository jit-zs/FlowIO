#include <iostream> 
#include <FlowIO/schema.hpp>
#include <cstring>
int main() {
    using namespace std::string_literals;
    using file_type = fio::schema_object<
        fio::schema_u64l,
        fio::schema_array_u64l<fio::schema_object<
        fio::schema_u8,
        fio::schema_null_string
        >>,
        fio::schema_null_string
        >;


    file_type writeObj = file_type();
    writeObj.get<0>() = 33;
    writeObj.get<1>().push_back(std::tuple{ fio::schema_u8(0x2A), fio::schema_null_string("const") });
    writeObj.get<1>().push_back(std::tuple{ fio::schema_u8(0x39), fio::schema_null_string("nair") });
    writeObj.get<2>() = "Fool";

    fio::binary_stream stream;
    stream.write_open("test_dir/schema_test.byte");
    std::cout << "Write: " << writeObj.write_to_stream(stream) << std::endl;;
    stream.close();

    file_type readObj;
    stream.read_open("test_dir/schema_test.byte");
    std::cout << "Read: " << readObj.read_validate_schema(stream) << std::endl;
    std::cout << "Match u64: " << (writeObj.get<0>() == readObj.get<0>()) << std::endl;
    std::cout << "Match string: " << (strcmp(writeObj.get<2>().data(), readObj.get<2>().data()) == 0) << std::endl;

    std::cout << "Match u8 1: " << (writeObj.get<1>()[0].get<0>() == readObj.get<1>()[0].get<0>()) << std::endl;
    std::cout << "Match u8 2: " << (writeObj.get<1>()[1].get<0>() == readObj.get<1>()[1].get<0>()) << std::endl;

    std::cout << "Match string 1: " << (strcmp(writeObj.get<1>()[0].get<1>().data(), readObj.get<1>()[0].get<1>().data()) == 0) << std::endl;
    std::cout << "Match string 2: " << (strcmp(writeObj.get<1>()[1].get<1>().data(), readObj.get<1>()[1].get<1>().data()) == 0) << std::endl;

    std::cout << "u64: " << readObj.get<0>() << std::endl;
    std::cout << "string: " << readObj.get<2>().data() << std::endl;

    std::cout << "arrObj1: {" << (int)readObj.get<1>()[0].get<0>() << ", " << readObj.get<1>()[0].get<1>().data() << "}" << std::endl;
    std::cout << "arrObj2: {" << (int)readObj.get<1>()[1].get<0>() << ", " << readObj.get<1>()[1].get<1>().data() << "}" << std::endl;
    stream.close();


    uint32_t og = 0x33221199;
    uint32_t swapped = fio::byteswap(og);
    std::cout << "Og: " << std::hex << og << std::endl;
    std::cout << "Swapped: " << std::hex << swapped << std::endl;

    std::cout << "Endianness: " << ((int)fio::get_platform_endian() ? "Little" : "Big") << std::endl;
}