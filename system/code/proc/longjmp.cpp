//
// \file longjmp.cpp
// \brief longjmp.cpp list setjmp() and longjmp() usage.
//

#include <setjmp.h>     // for setjmp()/longjmp() api.
#include <iostream>
#include <header.h>

static jmp_buf env;

static void f2(void) {
    longjmp(env, 2);
}

static void f1(int argc) {
    if (argc == 1)
        longjmp(env, 1);
    f2();
}

int main(int argc, char *argv[]) {

    switch (setjmp(env)) {
    case 0:
        std::cout << "initialize call setjmp()..." << std::endl;
        f1(argc);
        break;
    case 1:
        std::cout << "we jumped back from f1()..." << std::endl;
        break;
    case 2:
        std::cout << "we jumped back from f2()..." << std::endl;
        break;
    }

    return 0;
}
