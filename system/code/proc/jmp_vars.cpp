//
// \file jmp_vars.cpp
// \brief jmp_vars.cpp for setjmp() will be optimized by compiler.
//

#include <string>
#include <iostream>
#include <setjmp.h>
#include <header.h>

static jmp_buf env;

static void do_jump(int v1, int v2, int v3) {
    std::cout << "Inside do_jump(): v1=" << v1 << ", v2=" << v2 << ", v3=" << v3 << std::endl;
    longjmp(env, 1);
}

int main(int argc, char *argv[]) {
    int v1 = 111;
    register int v2 = 222;
    volatile int v3 = 333;

    if (setjmp(env) == 0) {
        v1 = 777;
        v2 = 888;
        v3 = 999;
        do_jump(v1, v2, v3);
    } else {
        std::cout << "after longjmp(): v1=" << v1 << ", v2=" << v2 << ", v3=" << v3 << std::endl;
    }

    return 0;
}

// compile the code with -O option and NO -O option will be output different.
//  variable v1 and v2 will be different when use -O option.
