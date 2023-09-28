
#ifndef __BX_CODE_ENV_ISA_H__
#define __BX_CODE_ENV_ISA_H__

typedef struct __bx_code_env_t__
{
    __BX_CODE_T__ __rom_data__ [BX_CODE_LEN_MAX];
    __BX_ADDR_T__ __rom_idx__;
} __bx_code_env_t__;

int __bx_code_dump_bin__(__bx_code_env_t__* __bx_code_env__, const char* filename);
int __bx_code_dump_hex__(__bx_code_env_t__* __bx_code_env__, const char* filename);
int __bx_code_dump_verilog__(__bx_code_env_t__* __bx_code_env__, const char* filename, const char* modulename);


#endif /* __BX_CODE_ENV_ISA_H__ */
