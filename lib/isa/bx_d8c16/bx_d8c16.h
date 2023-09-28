
#ifndef __BX_D8C16_H__
#define __BX_D8C16_H__
#define __BX_CODE_ISA_BX_D8C16__

#define BX_CODE_LEN_MAX 65536

#define __BX_ADDR_T__ __UINT64_TYPE__
#define __BX_CODE_T__ __UINT16_TYPE__
#define __BX_DATA_T__ __UINT8_TYPE__

#include <lib/code_env/code_env_isa.h>



#define __BX_INST8_T__ __UINT8_TYPE__
#define __BX_INST11_T__ __UINT16_TYPE__
#define __BX_INST12_T__ __UINT16_TYPE__

#define opi8(o, i8, c, d, e, f) \
    __BX_CODE_ENV_SET_CODE_INC_IDX__( __bx_d8c16_op_i8_code(o, i8, c, d, e, f) )

#define opi11(o, i11, f) \
    __BX_CODE_ENV_SET_CODE_INC_IDX__( __bx_d8c16_op_i11_code(o, i11, f) )

#define opi12(o, i12) \
    __BX_CODE_ENV_SET_CODE_INC_IDX__( __bx_d8c16_op_i12_code(o, i12) )

#define nop() \
    __BX_CODE_ENV_SET_CODE_INC_IDX__( ((__BX_CODE_T__)0) )

#define op(o, i8, c, d, e, f)   opi8(   o,      i8,     c, d, e, f)
#define d_inc_i(i8)             opi8(   0x2,    i8,     0, 0, 0, 0)
#define d_dec_i(i8)             opi8(   0x2,    i8,     0, 0, 0, 1)
#define d_set_i(i8)             opi8(   0xA,    i8,     0, 0, 0, 0)
#define d_set_d()               opi8(   0xA,    0x00,   0, 1, 0, 0)
#define s_inc_i(i11)            opi11(  0x6,    i11,             0)
#define s_dev_i(i11)            opi11(  0x6,    i11,             1)
#define d_set_li(i8)            opi8(   0xE,    i8,     0, 0, 0, 0)
#define d_set_hi(i8)            opi8(   0xE,    i8,     1, 0, 0, 0)
#define d_set_ld()              opi8(   0xE,    0x00,   0, 1, 0, 0)
#define d_set_hd()              opi8(   0xE,    0x00,   1, 1, 0, 0)
#define jmp_inc(i11)            opi11(  0x1,    i11,             0)
#define jmp_dec(i11)            opi11(  0x1,    i11,             1)
#define jmp_set(i12)            opi12(  0x9,    i12               )
#define jz_inc(i11)             opi11(  0xD,    i11,             0)
#define jz_dec(i11)             opi11(  0xD,    i11,             1)
#define jnz_inc(i11)            opi11(  0x5,    i11,             0)
#define jnz_dec(i11)            opi11(  0x5,    i11,             1)
#define in()                    opi8(   0xB,    0x00,   0, 0, 0, 0)
#define out_i(i8)               opi8(   0x3,    i8,     0, 0, 0, 0)
#define out_d()                 opi8(   0x3,    0x00,   0, 1, 0, 0)

__BX_CODE_T__ __bx_d8c16_op_i8_code(
    __UINT8_TYPE__ o,
    __BX_INST8_T__ i8,
    __UINT8_TYPE__ c,
    __UINT8_TYPE__ d,
    __UINT8_TYPE__ e,
    __UINT8_TYPE__ f
);

__BX_CODE_T__ __bx_d8c16_op_i11_code(
    __UINT8_TYPE__ o,
    __BX_INST11_T__ i11,
    __UINT8_TYPE__ c,
    __UINT8_TYPE__ d,
    __UINT8_TYPE__ e,
    __UINT8_TYPE__ f
);

__BX_CODE_T__ __bx_d8c16_op_i12_code(
    __UINT8_TYPE__ o,
    __BX_INST12_T__ i12,
    __UINT8_TYPE__ c,
    __UINT8_TYPE__ d,
    __UINT8_TYPE__ e,
    __UINT8_TYPE__ f
);



#endif /* __BX_D8C16_H__ */
