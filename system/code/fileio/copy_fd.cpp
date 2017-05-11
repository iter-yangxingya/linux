//
// \file copy_fd.cpp
// \brief copy_fd.cpp for copy fd methods: dup(), dup2(), dup3(), fcntl();
//

#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <iostream>
#include <header.h>

void my_dup();
void my_dup2();
void my_dup3();
void my_fcntl();
void my_fcntl2();

int main() {
    my_fcntl2();
    return 0;
}

void my_dup() {
    close(STDERR_FILENO);
    int fd;
    if ((fd = dup(STDOUT_FILENO)) == -1)
        error_exit("dup");

    std::vector<char> buf(1024);
    ssize_t len;
    while ((len = read(STDIN_FILENO, &buf[0], buf.size())) > 0) {
        if (write(STDOUT_FILENO, &buf[0], len) != len)
            error_exit("write");

        if (write(STDERR_FILENO, &buf[0], len) != len)
            error_exit("write");
    }
}

void my_dup2() {
    int fd;
    if ((fd = dup2(STDOUT_FILENO, STDERR_FILENO)) == -1)
        error_exit("dup2");

    std::vector<char> buf(1024);
    ssize_t len;
    while ((len = read(STDIN_FILENO, &buf[0], buf.size())) > 0) {
        if (write(STDOUT_FILENO, &buf[0], len) != len)
            error_exit("write");

        if (write(STDERR_FILENO, &buf[0], len) != len)
            error_exit("write");
    }
}

void my_dup3() {
    int fd;
    if ((fd = dup3(STDOUT_FILENO, STDERR_FILENO, O_CLOEXEC)) == -1)
        error_exit("dup3");

    std::vector<char> buf(1024);
    ssize_t len;
    while ((len = read(STDIN_FILENO, &buf[0], buf.size())) > 0) {
        if (write(STDOUT_FILENO, &buf[0], len) != len)
            error_exit("write");

        if (write(STDERR_FILENO, &buf[0], len) != len)
            error_exit("write");
    }
}

void my_fcntl() {
    int fd;
    if ((fd = fcntl(STDOUT_FILENO, F_DUPFD, STDERR_FILENO)) == -1)
        error_exit("fcntl");

    std::vector<char> buf(1024);
    ssize_t len;
    while ((len = read(STDIN_FILENO, &buf[0], buf.size())) > 0) {
        if (write(STDOUT_FILENO, &buf[0], len) != len)
            error_exit("write");

        if (write(STDERR_FILENO, &buf[0], len) != len)
            error_exit("write");
    }
}

void my_fcntl2() {
    int fd;
    if ((fd = fcntl(STDOUT_FILENO, F_DUPFD_CLOEXEC, STDERR_FILENO)) == -1)
        error_exit("fcntl");

    std::vector<char> buf(1024);
    ssize_t len;
    while ((len = read(STDIN_FILENO, &buf[0], buf.size())) > 0) {
        if (write(STDOUT_FILENO, &buf[0], len) != len)
            error_exit("write");

        if (write(STDERR_FILENO, &buf[0], len) != len)
            error_exit("write");
    }
}
