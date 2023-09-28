

#include <lib/isa/bf/bf.h>
#include <lib/code_env/code_env.h>

#define BX_CODE_LEN_MAX 16

def_bx_code(main_bf)
{
    nop;
    in;
    doWhile;
    shr;
    inc;
    shl;
    dec;
    doneUntil;
    shr;
    out;
}
