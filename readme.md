## Flow IO
Flow IO is a crossplatform C++20 IO library that aids in the saving, loading and validation of binary files.
## Schema Examples
Schema Write
```cpp
#include <FlowIO/FlowIO.hpp>

int main(){
    using file_type = fio::schema_object<fio::schema_u8, fio::schema_null_string, fio::schema_array_u32l<fio::schema_u8>>;
    file_type obj;
    obj.get<0>() = 2;
    obj.get<1>() = "Working";
    obj.get<2>().resize(12);
    for (size_t i = 0; i < obj.get<2>().size(); i++){
        obj.get<2>()[i] = i + 1;
    }


    fio::binary_stream stream;
    stream.write_open("example.byte");

    obj.write_to_stream(stream);

    stream.close();
}
```
Schema Read
```cpp
#include <FlowIO/FlowIO.hpp>

int main(){
    using file_type = fio::schema_object<fio::schema_u8, fio::schema_null_string, fio::schema_array_u32l<fio::schema_u8>>;
    file_type obj;

    fio::binary_stream stream;
    stream.read_open("example.byte");

    obj.read_validate_schema(stream);

    stream.close();
}

```
## Binary Stream Examples
Read
```cpp
#include <FlowIO/FlowIO.hpp>

int main(){
    fio::binary_stream stream;
    stream.write_open("example.byte");

    try {
        // stream.write(exampleData, exampleSize); ...
        stream.close();
    }
    catch(fio::error& err){
        std::cout << "Failed saving example.txt due to'" << err.what() << "'" << std::endl;
    }
}
```
Write
``` cpp
#include <FlowIO/FlowIO.hpp>

int main(){
    fio::binary_stream stream;
    stream.read_open("example.byte");

    try {
        // stream.read(exampleBuffer, exampleSize); ...
        stream.close();
    }
    catch(fio::error& err){
        std::cout << "Failed loading example.txt due to '" << err.what() << "'" << std::endl;
    }
}
```
## Feedback
All feedback is welcome, from suggestions to security errors. I am eager to help. Just submit them through an issue. 
## Goal
I want this library to have the ability to represent most file formats without the need to implement a custom class to implement read and write functions


