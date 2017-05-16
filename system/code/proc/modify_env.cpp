//
// \file modify_env.cpp
// \brief modify_env.cpp for modify environment ...
//

#if !defined(_GNU_SOURCE) // for stdlib.h declare variable.
# define _GUN_SOURCE
#endif

#include <stdlib.h>
#include <iostream>
#include <header.h>

extern char **environ;  // declare stdlib.h.

int main(int argc, char *argv[]) {

    // clear all environment.
    // it is not a SUV3 special.
    clearenv();

    // if have <name>=<value> environ pair, will put env.
    for (int i = 1; i < argc; i++)
        if (putenv(argv[i]) != 0)
            error_exit("putenv");

    // putenv() argument must be a global variable...
    // MUST NOT be a stack variable.
    // setenv() NO NEED like putenv(), the argument will can be a stack variable
    // because it will copy once to environment.

    if (setenv("GREET", "hello, world", 0) == -1)
        error_exit("setenv");

    for (char **ep = environ; *ep != nullptr; ep++)
        std::cout << *ep << std::endl;

    return 0;
}
