#include <iostream>
#include <FlowIO/binary_stream.hpp>
#include <FlowIO/assert.hpp>
#include <filesystem>
int main(int argc, char* argv[]) {
    fio::binary_stream stream;
    std::filesystem::path testFile = "test_dir/binary_stream_test_file.byte";
    stream.write_open(testFile);
    try {
        stream.write("\x22\xFF", 2);
        stream.close();
    }
    catch (fio::io_error& ex) {

    }



    char readBytes[2];
    stream.read_open(testFile);
    stream.read(readBytes, 2);
    stream.close();
    for (char c : readBytes) {
        std::cout << (int)c << std::endl;
    }
    return 0;
}