//
// \file fstat.cpp
// \brief fstat.cpp for file stat get or set.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <header.h>

void print_flags(int fd);

int main(int argc, char *argv[]) {
    std::string usage = argv[0];
    usage += "<file>";
    std::string file;
    if (argc == 2) {
        std::string argv1 = argv[1];
        if (argv1 == "--help" || argv1 == "-h")
            usage_error(usage.c_str());
        file = argv1;
    }

    if (file.empty())
        usage_error(usage.c_str());

    int fd;
    if ((fd = open(file.c_str(), O_RDONLY)) == -1)
        error_exit("open");

    print_flags(fd);
    std::cout << "stdin flags: " << std::endl;
    print_flags(STDIN_FILENO);
    std::cout << "stdout flags: " << std::endl;
    print_flags(STDOUT_FILENO);
    std::cout << "stderr flags: " << std::endl;
    print_flags(STDERR_FILENO);

    if (close(fd) == -1)
        error_exit("close");
    return 0;
}

void print_flags(int fd) {
    int flags;
    if ((flags = fcntl(fd, F_GETFL)) == -1)
        error_exit("fcntl");

    std::cout << "flags list";

    std::string out = "[";

    int rw = flags & O_ACCMODE;
    if (rw == O_RDONLY || rw == O_RDWR)
        out += "read, ";
    if (rw == O_WRONLY || rw == O_RDWR)
        out += "write, ";

#define IF_FLAG(flg, out, name) \
    if (flg & name) out += #name ", ";

    IF_FLAG(flags, out, O_CLOEXEC);
    IF_FLAG(flags, out, O_CREAT);
    IF_FLAG(flags, out, O_DIRECT);
    IF_FLAG(flags, out, O_DIRECTORY);
    IF_FLAG(flags, out, O_EXCL);
    IF_FLAG(flags, out, O_LARGEFILE);
    IF_FLAG(flags, out, O_NOATIME);
    IF_FLAG(flags, out, O_NOCTTY);
    IF_FLAG(flags, out, O_NOFOLLOW);
    IF_FLAG(flags, out, O_TRUNC);
    IF_FLAG(flags, out, O_APPEND);
    IF_FLAG(flags, out, O_ASYNC);
    IF_FLAG(flags, out, O_DSYNC);
    IF_FLAG(flags, out, O_NONBLOCK);
    IF_FLAG(flags, out, O_SYNC);

    out += "]";
    std::cout << out << std::endl;
}
