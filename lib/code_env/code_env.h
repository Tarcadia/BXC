
#ifndef __BX_CODE_ENV_H__
#define __BX_CODE_ENV_H__

#include "code_env_debug.h"

// I feel good for this idea of using C tools to compile the BX Code as
//  a macro in C and using C as a macro for BX Code. This can fully reuse
//  the C tool chain so I will not need to make a compiler from scratch.
//  And I can not only reuse the Lexer and Parser of C but also reusing
//  all of the tool chain like the IDE and Lint tools.

#define def_bx_code(name) \
    __bx_code_env_t__ __bx_code_env_##name##__;\
    void __bx_code_func_##name##__(__bx_code_env_t__* __bx_code_env__);\
    int __bx_code_dump_bin_##name##__(const char* filename)\
        {__bx_code_dump_bin__(&__bx_code_env_##name##__, filename);}\
    int __bx_code_dump_hex_##name##__(const char* filename)\
        {__bx_code_dump_hex__(&__bx_code_env_##name##__, filename);}\
    int __bx_code_dump_verilog_##name##__(const char* filename, const char* modulename)\
        {__bx_code_dump_verilog__(&__bx_code_env_##name##__, filename, modulename);}\
    int __bx_code_genrate_##name##__() {\
        __bx_code_func_##name##__(&__bx_code_env_##name##__);\
    }\
    void __bx_code_func_##name##__(__bx_code_env_t__* __bx_code_env__)

#define include_bx_code(name)\
    int __bx_code_dump_bin_##name##__(const char* filename);\
    int __bx_code_dump_hex_##name##__(const char* filename);\
    int __bx_code_dump_verilog_##name##__(const char* filename, const char* modulename);\
    int __bx_code_genrate_##name##__();\

#define generate_bx_code(name, type, ...) {\
    __bx_code_genrate_##name##__();\
    __bx_code_dump_##type##_##name##__(__VA_ARGS__);\
}



#define __BX_CODE_ENV_SET_CODE_INC_IDX__(code) {\
    if (__bx_code_env__->__rom_idx__ == BX_CODE_LEN_MAX)\
    {\
        __BX_CODE_ENV_DBG_PRINT__(\
            "ERROR: Run out of ROM storage of size %d.",\
            BX_CODE_LEN_MAX\
        );\
        return;\
    }\
    else\
    {\
        __bx_code_env__->__rom_data__[__bx_code_env__->__rom_idx__] = (code);\
        __bx_code_env__->__rom_idx__ += 1;\
    }\
}

#endif /* __BX_CODE_ENV_H__ */
