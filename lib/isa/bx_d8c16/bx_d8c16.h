
#ifndef __BX_D8C16_H__
#define __BX_D8C16_H__
#define __BX_CODE_ISA_BX_D8C16__

#define BX_CODE_LEN_MAX 65536

#define __BX_ADDR_T__ __UINT64_TYPE__
#define __BX_CODE_T__ __UINT16_TYPE__
#define __BX_DATA_T__ __UINT8_TYPE__

#include <code_env/code_env_isa.h>



#define __BX_INST8_T__ __UINT8_TYPE__
#define __BX_INST11_T__ __UINT16_TYPE__
#define __BX_INST12_T__ __UINT16_TYPE__

#define _opcode_opi8(o, i8, c, d, e, f) __bx_d8c16_op_i8_code(o, i8, c, d, e, f)
#define _opcode_opi11(o, i11, f)        __bx_d8c16_op_i11_code(o, i11, f)
#define _opcode_opi12(o, i12)           __bx_d8c16_op_i12_code(o, i12)
#define _opcode_nop()                   ((__BX_CODE_T__)0)

#define _opcode_op(o, i8, c, d, e, f)   _opcode_opi8(   o,      i8,     c, d, e, f)
#define _opcode_d_inc_i(i8)             _opcode_opi8(   0x2,    i8,     0, 0, 0, 0)
#define _opcode_d_dec_i(i8)             _opcode_opi8(   0x2,    i8,     0, 0, 0, 1)
#define _opcode_d_set_i(i8)             _opcode_opi8(   0xA,    i8,     0, 0, 0, 0)
#define _opcode_d_set_d()               _opcode_opi8(   0xA,    0x00,   0, 1, 0, 0)
#define _opcode_s_inc_i(i11)            _opcode_opi11(  0x6,    i11,             0)
#define _opcode_s_dev_i(i11)            _opcode_opi11(  0x6,    i11,             1)
#define _opcode_d_set_li(i8)            _opcode_opi8(   0xE,    i8,     0, 0, 0, 0)
#define _opcode_d_set_hi(i8)            _opcode_opi8(   0xE,    i8,     1, 0, 0, 0)
#define _opcode_d_set_ld()              _opcode_opi8(   0xE,    0x00,   0, 1, 0, 0)
#define _opcode_d_set_hd()              _opcode_opi8(   0xE,    0x00,   1, 1, 0, 0)
#define _opcode_jmp_inc(i11)            _opcode_opi11(  0x1,    i11,             0)
#define _opcode_jmp_dec(i11)            _opcode_opi11(  0x1,    i11,             1)
#define _opcode_jmp_set(i12)            _opcode_opi12(  0x9,    i12               )
#define _opcode_jz_inc(i11)             _opcode_opi11(  0xD,    i11,             0)
#define _opcode_jz_dec(i11)             _opcode_opi11(  0xD,    i11,             1)
#define _opcode_jnz_inc(i11)            _opcode_opi11(  0x5,    i11,             0)
#define _opcode_jnz_dec(i11)            _opcode_opi11(  0x5,    i11,             1)
#define _opcode_in()                    _opcode_opi8(   0xB,    0x00,   0, 0, 0, 0)
#define _opcode_out_i(i8)               _opcode_opi8(   0x3,    i8,     0, 0, 0, 0)
#define _opcode_out_d()                 _opcode_opi8(   0x3,    0x00,   0, 1, 0, 0)

#define nop()                   __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_nop())
#define op_opcode(opcode)       __BX_CODE_ENV_SET_CODE_INC_IDX__(opcode)
#define op(o, i8, c, d, e, f)   __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_op(o, i8, c, d, e, f))
#define d_inc_i(i8)             __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_d_inc_i(i8))
#define d_dec_i(i8)             __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_d_dec_i(i8))
#define d_set_i(i8)             __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_d_set_i(i8))
#define d_set_d()               __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_d_set_d())
#define s_inc_i(i11)            __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_s_inc_i(i11))
#define s_dec_i(i11)            __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_s_dev_i(i11))
#define s_set_li(i8)            __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_d_set_li(i8))
#define s_set_hi(i8)            __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_d_set_hi(i8))
#define s_set_ld()              __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_d_set_ld())
#define s_set_hd()              __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_d_set_hd())
#define jmp_inc(i11)            __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_jmp_inc(i11))
#define jmp_dec(i11)            __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_jmp_dec(i11))
#define jmp_set(i12)            __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_jmp_set(i12))
#define jz_inc(i11)             __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_jz_inc(i11))
#define jz_dec(i11)             __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_jz_dec(i11))
#define jnz_inc(i11)            __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_jnz_inc(i11))
#define jnz_dec(i11)            __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_jnz_dec(i11))
#define in()                    __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_in())
#define out_i(i8)               __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_out_i(i8))
#define out_d()                 __BX_CODE_ENV_SET_CODE_INC_IDX__(_opcode_out_d())

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
