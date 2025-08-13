## Flow IO
Flow IO is a crossplatform C++20 IO library that aids in the loading and validation of files
## Example
Write
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
Read
```cpp
#include <FlowIO/FlowIO.hpp>

int main(){
    using file_type = fio::schema_object<fio::schema_u8, fio::schema_null_string, fio::schema_array_u32l<fio::schema_u8>>;
    file_type obj;

    fio::binary_stream stream;
    stream.read_open("example.byte");

    obj.read_validate_schema(stream)

    stream.close();
}

```
## Feedback
All feedback is welcome. I am glad to help.
