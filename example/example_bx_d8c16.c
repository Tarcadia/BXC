

#include <isa/bx_d8c16/bx_d8c16.h>
#include <code_env/code_env.h>

def_bx_code(main_bx_d8c16)
{
    nop();
    d_inc_i(3);
    d_dec_i(3);
}
