
#include <code_env/code_env.h>

include_bx_code(main_bx_d8c16);
// include_bx_code(main_bf);

int main() {
    generate_bx_code(main_bx_d8c16, bin, "main_bx_d8c16.bin");
    // dump_bx_code(main_bf, bin, "main_bf.bin");
    return 0;
}
