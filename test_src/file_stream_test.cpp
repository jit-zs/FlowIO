#include <iostream>
#include <FlowIO/binary_stream.hpp>
#include <filesystem>
int main(int argc, char* argv[]) {
    fio::binary_stream stream;
    std::filesystem::path testFile = "test_dir/binary_stream_test_file.byte";

    std::filesystem::create_directory("test_dir");
    std::filesystem::remove(testFile);

    // Simulating successful write operation
    stream.write_open(testFile);
    try {
        stream.write("\x22\xFF", 2);
        stream.close();
    }
    catch (fio::io_error& ex) {
        std::cout << ex.what();
    }
    stream.close();


    // Simulating successful read operation
    char readBytes[2];
    stream.read_open(testFile);
    try {
        stream.read(readBytes, 2);
        stream.close();
    }
    catch (fio::io_error& ex){
        std::cout << ex.what() << std::endl;
    }
     stream.close();
    for (char c : readBytes) {
        std::cout << (int)c << std::endl;
    }
   

    // For simulating an out of bounds read error
    stream.read_open(testFile);
    try {
        stream.read(readBytes, 3);
        stream.close();
    }
    catch (fio::io_error& ex) {
        std::cout << ex.what();
    }
    stream.close();

    return 0;
}