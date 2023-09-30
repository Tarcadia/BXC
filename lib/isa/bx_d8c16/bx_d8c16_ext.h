
#ifndef __BX_D8C16_EXT_H__
#define __BX_D8C16_EXT_H__

#include "bx_d8c16.h"

#include <code_env/code_env_isa.h>
#include <code_env/code_env_debug.h>



#define label(name) __BX_ADDR_T__ __bx_code_env_label_##name##__ = __bx_code_env__->__rom_idx__;
#define atLabel(name) __bx_code_env_label_##name##__

#define _do_alloc_a(loc) {\
    if ( (loc & 0xFFFFFFFFFFFF0000) == 0x0000000000000000 )\
    {\
        s_set_li(loc & 0x00000000000000FF);\
        s_set_hi(loc & 0x000000000000FF00);\
    }\
    else\
    {\
        __BX_CODE_ENV_DBG_PRINT__(\
            "WARNING: Too big data address, allocating may miss."\
        );\
    }\
}

#define _do_alloc_b(from, to) {\
    if ( (from & 0xFFFFFFFFFFFFFF00) == (to & 0xFFFFFFFFFFFFFF00) )\
    {\
        s_set_li(to & 0x00000000000000FF);\
    }\
    else if ( from < to && (to - from) < (2 << 11) )\
    {\
        s_inc_i(to - from);\
    }\
    else if ( from > to && (from - to) < (2 << 11) )\
    {\
        s_dec_i(from - to);\
    }\
    else if ( (from & 0xFFFFFFFFFFFF0000) == (to & 0xFFFFFFFFFFFF0000) )\
    {\
        s_set_li(to & 0x00000000000000FF);\
        s_set_hi(to & 0x000000000000FF00);\
    }\
    else\
    {\
        __BX_CODE_ENV_DBG_PRINT__(\
            "ERROR: Too big data address or data address gap."\
        );\
        return;\
    }\
}

#define _do_jmp(from, to) {\
    if ( from >= to ) {\
        if ( from - to < (2 << 11) )\
        {\
            jmp_dec(from - to);\
        }\
        else if ( to < (2 << 12) ) \
        {\
            jmp_set(to);\
        }\
        else __BX_CODE_ENV_DBG_PRINT__(\
            "ERROR: Too long code gap to jump."\
        );\
        return;\
    }\
    else {\
        if ( to - from < (2 << 11) )\
        {\
            jmp_dec(to - from);\
        }\
        else if ( to < (2 << 12) ) \
        {\
            jmp_set(to);\
        }\
        else __BX_CODE_ENV_DBG_PRINT__(\
            "ERROR: Too long code gap to jump."\
        );\
        return;\
    }\
}

#define _do_jmp_con(zORnz, from, to) {\
    if ( (from >= to) && (from - to < (2 << 11)) )\
    {\
        j##zORnz##_dec(from - to);\
    }\
    else if ( (from < to) && (to - from < (2 << 11)) )\
    {\
        j##zORnz##_dec(to - from);\
    }\
    else __BX_CODE_ENV_DBG_PRINT__(\
        "ERROR: Too long code gap to jump."\
    );\
    return;\
}

#define _refill_jmp(from, to) {\
    if ( from >= to ) {\
        if ( from - to < (2 << 11) )\
        {\
            __bx_code_env__->__rom_data__[from] = _opcode_jmp_dec(from - to);\
        }\
        else if ( to < (2 << 12) ) \
        {\
            __bx_code_env__->__rom_data__[from] = _opcode_jmp_set(to);\
        }\
        else __BX_CODE_ENV_DBG_PRINT__(\
            "ERROR: Too long code gap to jump."\
        );\
        return;\
    }\
    else {\
        if ( to - from < (2 << 11) )\
        {\
            __bx_code_env__->__rom_data__[from] = _opcode_jmp_dec(to - from);\
        }\
        else if ( to < (2 << 12) ) \
        {\
            __bx_code_env__->__rom_data__[from] = _opcode_jmp_set(to);\
        }\
        else __BX_CODE_ENV_DBG_PRINT__(\
            "ERROR: Too long code gap to jump."\
        );\
        return;\
    }\
}

#define _refill_jmp_con(zORnz, from, to) {\
    if ( (from >= to) && (from - to < (2 << 11)) )\
    {\
        __bx_code_env__->__rom_data__[from] = _opcode_j##zORnz##_dec(from - to);\
    }\
    else if ( (from < to) && (to - from < (2 << 11)) )\
    {\
        __bx_code_env__->__rom_data__[from] = _opcode_j##zORnz##_dec(to - from);\
    }\
    else __BX_CODE_ENV_DBG_PRINT__(\
        "ERROR: Too long code gap to jump."\
    );\
    return;\
}

#define do_always(code) {\
    __BX_ADDR_T__ __bx_code_at_always_begin_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    {code};\
    __BX_ADDR_T__ __bx_code_at_always_done_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    __BX_ADDR_T__ __bx_code_at_always_break_##__LINE__##__ = __bx_code_env__->__rom_idx__ + 1;\
    _do_jmp(__bx_code_at_always_done_##__LINE__##__, __bx_code_at_always_begin_##__LINE__##__);\
}

#define do_while_pre_con_post(code_pre_con, code_post_con, zORnzREV, code_while) {\
    __BX_ADDR_T__ __bx_code_at_while_begin_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    {code_pre_con};\
    __BX_ADDR_T__ __bx_code_at_while_jmp_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    j##zORnzREV##_inc(0);\
    {code_post_con};\
    {code_while};\
    __BX_ADDR_T__ __bx_code_at_while_done_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    __BX_ADDR_T__ __bx_code_at_while_break_##__LINE__##__ = __bx_code_env__->__rom_idx__ + 1;\
    _refill_jmp_con(zORnzREV, __bx_code_at_while_jmp_##__LINE__##__, __bx_code_at_while_break_##__LINE__##__);\
    _do_jmp(__bx_code_at_while_done_##__LINE__##__, __bx_code_at_while_begin__);\
}

#define do_while_zero(code) {\
    __BX_ADDR_T__ __bx_code_at_while_zero_begin_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    jnz_inc(0);\
    {code};\
    __BX_ADDR_T__ __bx_code_at_while_zero_done_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    __BX_ADDR_T__ __bx_code_at_while_zero_break_##__LINE__##__ = __bx_code_env__->__rom_idx__ + 1;\
    _refill_jmp_con(nz, __bx_code_at_while_zero_begin_##__LINE__##__, __bx_code_at_while_zero_break_##__LINE__##__);\
    _do_jmp(__bx_code_at_while_zero_done_##__LINE__##__, __bx_code_at_while_zero_begin_##__LINE__##__);\
}

#define do_while_nzero(code) {\
    __BX_ADDR_T__ __bx_code_at_while_nzero_begin_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    jz_inc(0);\
    {code};\
    __BX_ADDR_T__ __bx_code_at_while_nzero_done_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    __BX_ADDR_T__ __bx_code_at_while_nzero_break_##__LINE__##__ = __bx_code_env__->__rom_idx__ + 1;\
    _refill_jmp_con(z, __bx_code_at_while_nzero_begin_##__LINE__##__, __bx_code_at_while_nzero_break_##__LINE__##__);\
    _do_jmp(__bx_code_at_while_nzero_done_##__LINE__##__, __bx_code_at_while_nzero_begin_##__LINE__##__);\
}

#define do_if_greater(low, code_if, code_else, _loc, _tmp_if_low, _tmp_rev_loc) {\
    _do_alloc_a(_tmp_if_low);\
    d_set_i(0);\
    _do_alloc_b(_tmp_if_low, _tmp_rev_loc);\
    d_set_i(0);\
    do_move_2(_loc, _tmp_if_low, _tmp_rev_loc);\
    do_move(_tmp_rev_loc, _loc);\
    _do_alloc_b(_tmp_if_low);\
        __BX_ADDR_T__ __bx_code_at_if_##__LINE__##__;\
    do_while_nzero({\
        d_dec_i(low);\
        __bx_code_at_if_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
        jz_inc(0);\
        d_inc_i(low-1);\
    })\
    _do_alloc_a(_loc);\
    {code_else}\
    __BX_ADDR_T__ __bx_code_at_else_done_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    jmp_inc(0);\
    __BX_ADDR_T__ __bx_code_at_then_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    _do_alloc_a(_loc);\
    {code_if}\
    __BX_ADDR_T__ __bx_code_at_if_break_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    _refill_jmp_con(z, __bx_code_at_if_##__LINE__##__, __bx_code_at_then_##__LINE__##__);\
    _refill_jmp(__bx_code_at_else_done_##__LINE__##__, __bx_code_at_if_break_##__LINE__##__);\
}

#define do_if_lesser(high, code_if, code_else, _loc, _tmp_if_high, _tmp_rev_loc) {\
    _do_alloc_a(_tmp_if_high);\
    d_set_i(0);\
    _do_alloc_b(_tmp_if_high, _tmp_rev_loc);\
    d_set_i(0);\
    do_move_2(_loc, _tmp_if_high, _tmp_rev_loc);\
    do_move(_tmp_rev_loc, _loc);\
    _do_alloc_b(_tmp_if_high);\
        __BX_ADDR_T__ __bx_code_at_if_##__LINE__##__;\
    do_while_nzero({\
        d_dec_i(high);\
        __bx_code_at_if_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
        jz_inc(0);\
        d_inc_i(high+1);\
    })\
    _do_alloc_a(_loc);\
    {code_else}\
    __BX_ADDR_T__ __bx_code_at_else_done_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    jmp_inc(0);\
    __BX_ADDR_T__ __bx_code_at_then_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    _do_alloc_a(_loc);\
    {code_if}\
    __BX_ADDR_T__ __bx_code_at_if_break_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    _refill_jmp_con(z, __bx_code_at_if_##__LINE__##__, __bx_code_at_then_##__LINE__##__);\
    _refill_jmp(__bx_code_at_else_done_##__LINE__##__, __bx_code_at_if_break_##__LINE__##__);\
}

#define do_if_range(low, high, code_if, code_else, _loc, _tmp_if_high, _tmp_if_low, _tmp_rev_loc) {\
    _do_alloc_a(_tmp_if_high);\
    d_set_i(0);\
    _do_alloc_b(_tmp_if_high, _tmp_if_low);\
    d_set_i(0);\
    _do_alloc_b(_tmp_if_low, _tmp_rev_loc);\
    d_set_i(0);\
    do_move_3(_loc, _tmp_if_high, _tmp_if_low, _tmp_rev_loc);\
    do_move(_tmp_rev_loc, _loc);\
    _do_alloc_a(_tmp_if_high);\
    __BX_ADDR_T__ __bx_code_at_if_high_##__LINE__##__;\
    do_while_nzero({\
        d_dec_i(high);\
        __bx_code_at_if_high_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
        jz_inc(0);\
        d_inc_i(high+1);\
    })\
    __BX_ADDR_T__ __bx_code_at_if_not_high_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    jmp_inc(0);\
    __BX_ADDR_T__ __bx_code_at_if_high_then_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    _do_alloc_a(_tmp_if_high);\
    __BX_ADDR_T__ __bx_code_at_if_low_##__LINE__##__;\
    do_while_nzero({\
        d_dec_i(high);\
        __bx_code_at_if_low_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
        jz_inc(0);\
        d_inc_i(high+1);\
    })\
    __BX_ADDR_T__ __bx_code_at_else_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    _do_alloc_a(_loc);\
    {code_else}\
    __BX_ADDR_T__ __bx_code_at_else_done_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    jmp_inc(0);\
    __BX_ADDR_T__ __bx_code_at_if_low_then_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    _do_alloc_a(_loc);\
    {code_if}\
    __BX_ADDR_T__ __bx_code_at_if_break_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    _refill_jmp_con(z, __bx_code_at_if_high_##__LINE__##__, __bx_code_at_if_high_then_##__LINE__##__);\
    _refill_jmp_con(z, __bx_code_at_if_low_##__LINE__##__, __bx_code_at_if_low_then_##__LINE__##__);\
    _refill_jmp(__bx_code_at_if_not_high_##__LINE__##__, __bx_code_at_else_##__LINE__##__);\
    _refill_jmp(__bx_code_at_else_done_##__LINE__##__, __bx_code_at_if_break_##__LINE__##__);\
}

#define do_if_pre_con_post(code_pre_con, code_post_con, zORnz, code_if, code_else) {\
    {code_pre_con};\
    __BX_ADDR_T__ __bx_code_at_if_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    j##zORnz##_inc(0);\
    {code_post_con};\
    {code_else};\
    __BX_ADDR_T__ __bx_code_at_else_done_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    jmp_inc(0);\
    __BX_ADDR_T__ __bx_code_at_then_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    {code_post_con};\
    {code_if};\
    __BX_ADDR_T__ __bx_code_at_if_break_##__LINE__##__ = __bx_code_env__->__rom_idx__;\
    _refill_jmp_con(zORnz, __bx_code_at_if_##__LINE__##__, __bx_code_at_then_##__LINE__##__);\
    _refill_jmp(__bx_code_at_else_done_##__LINE__##__, __bx_code_at_if_break_##__LINE__##__);\
}

#define do_sub(from, to) {\
    _do_alloc_a(from);\
    do_while_nzero({\
        d_dec_i(1);\
        _do_alloc_b(from, to);\
        d_dec_i(1);\
        _do_alloc_b(to, from);\
    })\
}

#define do_move(from, to) {\
    _do_alloc_a(from);\
    do_while_nzero({\
        d_dec_i(1);\
        _do_alloc_b(from, to);\
        d_inc_i(1);\
        _do_alloc_b(to, from);\
    });\
}

#define do_move_2(from, to_0, to_1) {\
    _do_alloc_a(from);\
    do_while_nzero({\
        jz_inc(0);\
        d_dec_i(1);\
        _do_alloc_b(from, to_0);\
        d_inc_i(1);\
        _do_alloc_b(to_0, to_1);\
        d_inc_i(1);\
        _do_alloc_b(to_1, from);\
    });\
}

#define do_move_3(from, to_0, to_1, to_2) {\
    _do_alloc_a(from);\
    do_while_nzero({\
        d_dec_i(1);\
        _do_alloc_b(from, to_0);\
        d_inc_i(1);\
        _do_alloc_b(to_0, to_1);\
        d_inc_i(1);\
        _do_alloc_b(to_1, to_2);\
        d_inc_i(1);\
        _do_alloc_b(to_2, from);\
    });\
}

#define do_move_4(from, to_0, to_1, to_2, to_3) {\
    _do_alloc_a(from);\
    do_while_nzero({\
        d_dec_i(1);\
        _do_alloc_b(from, to_0);\
        d_inc_i(1);\
        _do_alloc_b(to_0, to_1);\
        d_inc_i(1);\
        _do_alloc_b(to_1, to_2);\
        d_inc_i(1);\
        _do_alloc_b(to_2, to_3);\
        d_inc_i(1);\
        _do_alloc_b(to_3, from);\
    });\
}

#define do_move_8(from, to_0, to_1, to_2, to_3, to_4, to_5, to_6, to_7) {\
    _do_alloc_a(from);\
    do_while_nzero({\
        d_dec_i(1);\
        _do_alloc_b(from, to_0);\
        d_inc_i(1);\
        _do_alloc_b(to_0, to_1);\
        d_inc_i(1);\
        _do_alloc_b(to_1, to_2);\
        d_inc_i(1);\
        _do_alloc_b(to_2, to_3);\
        d_inc_i(1);\
        _do_alloc_b(to_3, to_4);\
        d_inc_i(1);\
        _do_alloc_b(to_4, to_5);\
        d_inc_i(1);\
        _do_alloc_b(to_5, to_6);\
        d_inc_i(1);\
        _do_alloc_b(to_6, to_7);\
        d_inc_i(1);\
        _do_alloc_b(to_7, from);\
    });\
}


#endif /* __BX_D8C16_EXT_H__ */
