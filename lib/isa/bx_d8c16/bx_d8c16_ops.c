
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
