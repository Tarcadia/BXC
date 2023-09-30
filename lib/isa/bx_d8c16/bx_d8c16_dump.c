
#include "bx_d8c16.h"

#include <stdio.h>
#include <memory.h>

int __bx_code_dump_bin__(
    __bx_code_env_t__* __bx_code_env__,
    const char* filename
)
{
    unsigned char _buf [
        (sizeof(__BX_CODE_T__) * BX_CODE_LEN_MAX / sizeof(int)
        + !!(sizeof(__BX_CODE_T__) * BX_CODE_LEN_MAX % sizeof(int)))
        * sizeof(int)
    ];
    memset(_buf, 0, sizeof(_buf));
    for (__BX_ADDR_T__ _addr = 0; _addr < __bx_code_env__->__rom_idx__; _addr += 1)
    {
        __BX_CODE_T__ _mask = (__BX_CODE_T__)((unsigned char) -1);
        __BX_CODE_T__ _code = (__bx_code_env__->__rom_data__[_addr]) << (16 - sizeof(__BX_CODE_T__));
        int _i_buf = _addr * sizeof(__BX_CODE_T__) + sizeof(__BX_CODE_T__);
        switch (sizeof(__BX_CODE_T__))
        {
        // case 16:    _buf[--_i_buf] = (_code & (_mask << 120)) >> 120;
        // case 15:    _buf[--_i_buf] = (_code & (_mask << 112)) >> 112;
        // case 14:    _buf[--_i_buf] = (_code & (_mask << 104)) >> 104;
        // case 13:    _buf[--_i_buf] = (_code & (_mask <<  96)) >>  96;
        // case 12:    _buf[--_i_buf] = (_code & (_mask <<  88)) >>  88;
        // case 11:    _buf[--_i_buf] = (_code & (_mask <<  80)) >>  80;
        // case 10:    _buf[--_i_buf] = (_code & (_mask <<  72)) >>  72;
        // case 9:     _buf[--_i_buf] = (_code & (_mask <<  64)) >>  64;
        // case 8:     _buf[--_i_buf] = (_code & (_mask <<  56)) >>  56;
        // case 7:     _buf[--_i_buf] = (_code & (_mask <<  48)) >>  48;
        // case 6:     _buf[--_i_buf] = (_code & (_mask <<  40)) >>  40;
        // case 5:     _buf[--_i_buf] = (_code & (_mask <<  32)) >>  32;
        case 4:     _buf[--_i_buf] = (_code & (_mask <<  24)) >>  24;
        case 3:     _buf[--_i_buf] = (_code & (_mask <<  16)) >>  16;
        case 2:     _buf[--_i_buf] = (_code & (_mask <<   8)) >>   8;
        case 1:     _buf[--_i_buf] = (_code & (_mask <<   0)) >>   0;
        }
    }

    FILE* fp = fopen(filename, "w");
    for (int _i = 0; _i < sizeof(_buf); _i += 1) fputc(_buf[_i], fp);
    fclose(fp);
    return 0;
}

int __bx_code_dump_hex__(
    __bx_code_env_t__* __bx_code_env__,
    const char* filename
)
{
    // TODO: Implement this function.
    return 0;
}

int __bx_code_dump_verilog__(
    __bx_code_env_t__* __bx_code_env__,
    const char* filename,
    const char* modulename
)
{
    // TODO: Implement this function.
    return 0;
}
