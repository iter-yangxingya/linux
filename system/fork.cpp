//
// \file fork.cpp
// \brief fork.cpp for system api fork()
//      pid_t fork();
//      include file <sys/types.h> ===> pid_t, <unistd.h> ===> fork() api.
//

#include <sys/types.h>  // for ===> pid_t type.
#include <unistd.h>     // for fork() api declare.
#include <stdlib.h>     // for exit() api declare.
#include <iostream>

int main(int argc, char **argv) {
    //
    pid_t pid = getpid(); // getpid() for get current process id.
    std::cout << "current process id: " << pid << std::endl;

    pid = fork();
    if (pid < 0) {
        std::cout << "call fork() api failed, please check..." << std::endl;
        return -1;
    }

    if (pid > 0) {
        std::cout << "this is a parent process, will exit..." << std::endl;
        exit(0);
    }

    std::cout << "this is a child process..." << std::endl;

    while (true) {

    }

    return 0;
}
