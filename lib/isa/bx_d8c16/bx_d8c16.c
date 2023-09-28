#include "bx_d8c16.h"



__BX_CODE_T__ __bx_d8c16_op_i8_code(
    __UINT8_TYPE__ o,
    __BX_INST8_T__ i8,
    __UINT8_TYPE__ c,
    __UINT8_TYPE__ d,
    __UINT8_TYPE__ e,
    __UINT8_TYPE__ f
)
{
    return (__BX_CODE_T__)(
        (o & 0x000F)
        | ((i8 & 0x00FF) << 4)
        | (!!c << 12)
        | (!!d << 13)
        | (!!e << 14)
        | (!!f << 15)
    );
}

__BX_CODE_T__ __bx_d8c16_op_i11_code(
    __UINT8_TYPE__ o,
    __BX_INST11_T__ i11,
    __UINT8_TYPE__ c,
    __UINT8_TYPE__ d,
    __UINT8_TYPE__ e,
    __UINT8_TYPE__ f
)
{
    return (__BX_CODE_T__)(
        (o & 0x000F)
        | ((i11 & 0x07FF) << 4)
        | (!!f << 15)
    );
}

__BX_CODE_T__ __bx_d8c16_op_i12_code(
    __UINT8_TYPE__ o,
    __BX_INST12_T__ i12,
    __UINT8_TYPE__ c,
    __UINT8_TYPE__ d,
    __UINT8_TYPE__ e,
    __UINT8_TYPE__ f
)
{
    return (__BX_CODE_T__)(
        (o & 0x000F)
        | ((i12 & 0x0FFF) << 4)
    );
}



int __bx_code_dump_bin__(
    __bx_code_env_t__* __bx_code_env__,
    const char* filename
)
{
    // TODO: Implement this function.
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
