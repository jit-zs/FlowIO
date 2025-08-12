#ifndef FLOWIO_ENDIAN_HPP
#define FLOWIO_ENDIAN_HPP
#include <stdint.h>
namespace fio{
    enum class endian{
        big,
        little,
        none,
    };
    endian get_platform_endian(){
        union{
            uint32_t i;
            char c[4];
        } bint = {0x01020304};
        return bint.c[0] == 0x04 ? endian::little : endian::big;
    }
}

#endif