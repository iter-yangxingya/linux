//
// \file show_env.cpp
// \brief show_env.cpp for show environment variable by global variable: environ.
//

#include <iostream>
#include <header.h>

int main(/*int argc, char *argv[]*/) {
    for (char **ep = environ; *ep != nullptr; ep++)
        std::cout << *ep << std::endl;

    return 0;
}

// you can use shell for add environment:
//  $ export <NAME>=<VALUE>
// ex: $ export SHELL=/bin/bash
// you can use the following format:
//  $ SHELL=/bin/bash <app>
// then app has SHELL=/bin/bash environment and shell environment.
//
// /proc/<PID>/environ file has the environment...
