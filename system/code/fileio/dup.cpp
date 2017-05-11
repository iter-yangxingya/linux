//
// \file dup.cpp
// \brief dup.cpp implement dup()/dup2() with close() and fcntl().
//

#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <header.h>

int i_dup(int fd);
int i_dup2(int oldfd, int newfd);

int main() {

    int fd = i_dup(0);
    std::cout << "i_dup(0) = " << fd << std::endl;
    close(fd);
    std::cout << "dup(0) = " << dup(0) << std::endl;

    int oldfd = 0;
    int newfd = 1;

    std::cout << "i_dup2(" << oldfd << ", " << newfd << ") = " << i_dup2(oldfd, newfd) << std::endl;
    std::cout << "i_dup2(" << newfd << ", " << oldfd << ") = " << i_dup2(newfd, oldfd) << std::endl;

    return 0;
}

int i_dup(int fd) {
    return fcntl(fd, F_DUPFD, 0);
}

int i_dup2(int oldfd, int newfd) {
    // 1. check oldfd is validated.
    // 2. check newfd is opened, if opened, close it.
    // 3. call fcntl to dup new fd
    // 4. close oldfd

    // 1. check.
    if (fcntl(oldfd, F_GETFL) == -1) {
        errno = EBADF;
        return -1;
    }

    if (oldfd == newfd)
        return newfd;

    // 2. close newfd.
    if (fcntl(newfd, F_GETFL) != -1)
        close(newfd);

    // 3. call fcntl to dup newfd.
    int fd;
    if ((fd = fcntl(oldfd, F_DUPFD, newfd)) == -1) {
        // dup2() return value is different from fcntl() return value.
        //HACK: should set errno to dup2() matched value.
        return -1;
    }

    // close oldfd.
    close(oldfd);

    // HACK: fcntl() return value can be different from newfd, how to deal it.
    // spin_lock() methods to try until they are equal???

    return fd;
}
