#include <iostream>
#include <FlowIO/binary_stream.hpp>
#include <FlowIO/assert.hpp>
#include <filesystem>
int main(int argc, char* argv[]){
    fio::binary_stream stream;
    stream.write_open("test_dir/binary_stream_test_file.byte");
    try {
        stream.write("\x22\xFF", 2);
        stream.close();
    }
    catch (fio::io_error& ex) {
    
    }
    return 0;
}