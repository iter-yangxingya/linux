//
// \file t_readv.cpp
// \brief t_readv.cpp for readv() system call example...
//

#include <sys/stat.h>
#include <sys/uio.h>    // for readv()/writev()/preadv()/pwritev() system call.
#include <fcntl.h>
#include <vector>
#include <string>
#include <iostream>
#include <header.h>

int main(int argc, char *argv[]) {
    std::string usage = argv[0];
    usage += " <file>";
    if (argc != 2) {
        std::cout << "Invalid usage" << std::endl;
        usage_error(usage.c_str());
    }

    std::string arg = argv[1];
    if (arg == "--help" || arg == "-h")
        usage_error(usage.c_str());

    int fd;
    if ((fd = open(arg.c_str(), O_RDONLY)) == -1)
        error_exit("open");

    struct iovec iov[3];

    struct stat status;
    int x;
    std::vector<char> data(100);

    ssize_t total = 0;

    iov[0].iov_base = &status;
    iov[0].iov_len = sizeof(status);
    total += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    total += iov[1].iov_len;

    iov[2].iov_base = &data[0];
    iov[2].iov_len = data.size();
    total += iov[0].iov_len;

    ssize_t rlen;
    if ((rlen = readv(fd, iov, 3)) == -1)
        error_exit("readv");

    if (rlen < total)
        std::cout << "read length is less than requested" << std::endl;

    std::cout << "want read length is: " << total << ", read length is: " << rlen << std::endl;

    close(fd);
    return 0;
}
