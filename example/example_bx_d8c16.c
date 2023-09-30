

#include <isa/bx_d8c16/bx_d8c16.h>
#include <isa/bx_d8c16/bx_d8c16_ext.h>
#include <code_env/code_env.h>

def_bx_code(main_bx_d8c16)
{
    nop();
    in();
    label(loop_read);
    do_if_range('0', '9',
    {
        do_move_8(1, 2, 3, 3, 3, 3, 3, 3, 3);
        do_move_3(2, 3, 3, 3);
        do_move(3, 1);
        do_move(0, 1);
    },{
        label(loop_read_do);
        jmp_set(atLabel(loop_read));
    },
    0, 1, 2, 3);
    d_dec_i(3);
    do_while_nzero(
        d_inc_i(1);
    );
}
