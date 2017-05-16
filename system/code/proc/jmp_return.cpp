//
// file jmp_return.cpp
// brief jmp_return.cpp for jmp to has been return function.
//

#include <iostream>
#include <setjmp.h>

static jmp_buf env;

static
void jmp_return(int v) {
    std::cout << "Inside jmp_return() function will be return when call setjmp() after..." << std::endl;
    if (setjmp(env) == 0) {
        std::cout << "call setjmp() for initialize..." << std::endl;
        return;
    }
}

int main(int argc, char *argv[]) {

    jmp_return(1);
    std::cout << "jmp_return() function had been return..." << std::endl;

    longjmp(env, 1);
    std::cout << "longjmp() function call after..." << std::endl;

    return 0;
}
