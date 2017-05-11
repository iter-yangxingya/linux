//
// \file readv_writev.cpp
// \brief readv_writev.cpp for implement readv()/writev() use read()/write() api.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <vector>
#include <header.h>

ssize_t i_readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t i_writev(int fd, struct iovec *iov, int iovcnt);

int main(int argc, char *argv[]) {
    std::string usage = argv[0];
    usage += " <file>";
    if (argc != 2) {
        std::cout << "Invalid argument" << std::endl;
        usage_error(usage.c_str());
    }

    std::string arg = argv[1];
    if (arg == "--help" || arg == "-h")
        usage_error(usage.c_str());

    char data1[5] = "abcd";
    char data2[10] = "efghijklm";
    char data3[5] = "nopq";
    //char data3[50] = "nopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    struct iovec iov[3];
    size_t total = 0;

    iov[0].iov_base = data1;
    iov[0].iov_len = sizeof(data1);
    total += iov[0].iov_len;

    iov[1].iov_base = data2;
    iov[1].iov_len = sizeof(data2);
    total += iov[1].iov_len;

    iov[2].iov_base = data3;
    iov[2].iov_len = sizeof(data3);
    total += iov[2].iov_len;

    int fd;
    int flags = O_RDWR | O_CREAT | O_EXCL;
    mode_t mode = S_IRUSR | S_IWUSR;
    if ((fd = open(arg.c_str(), flags, mode)) == -1) {
        flags = O_RDWR | O_TRUNC;
        if ((fd = open(arg.c_str(), flags)) == -1)
            error_exit("open");
    }

    ssize_t rlen;
    if ((rlen = i_writev(fd, iov, 3)) == -1)
        error_exit("i_writev");

    std::cout << "write file length: " << total << ", real length is: " << rlen << std::endl;

    char out1[5] = {0};
    char out2[10] = {0};
    char out3[50] = {0};

    total = 0;
    iov[0].iov_base = out1;
    iov[0].iov_len = sizeof(out1);
    total += iov[0].iov_len;

    iov[1].iov_base = out2;
    iov[1].iov_len = sizeof(out2);
    total += iov[1].iov_len;

    iov[2].iov_base = out3;
    iov[2].iov_len = sizeof(out3);
    total += iov[2].iov_len;


    if (lseek(fd, 0, SEEK_SET) == -1)
        error_exit("lseek");

    if ((rlen = i_readv(fd, iov, 3)) == -1)
        error_exit("i_readv");

    std::cout << "read file length: " << total << ", real length is: " << rlen << std::endl;
    std::cout << "iov[0]: " << out1 << std::endl;
    std::cout << "iov[1]: " << out2 << std::endl;
    std::cout << "iov[2]: " << out3 << std::endl;

    return 0;
}

ssize_t i_readv(int fd, const struct iovec *iov, int iovcnt) {
    size_t total = 0;
    for (int i = 0; i < iovcnt; i++)
        total += iov[i].iov_len;

    std::vector<char> data(total);
    ssize_t rlen;
    if ((rlen = read(fd, &data[0], data.size())) > 0) {
        int pos = 0;
        size_t left = (size_t)rlen;
        size_t copy;
        for (int i = 0; i < iovcnt; i++) {
            if (left >= iov[i].iov_len) {
                copy = iov[i].iov_len;
                memcpy(iov[i].iov_base, &data[pos], copy);
            } else {
                copy = iov[i].iov_len - left;
                if (copy)
                    memcpy(iov[i].iov_base, &data[pos], copy);
                break;
            }
            pos += copy;
            left -= copy;
        }
    }

    return rlen;
}

ssize_t i_writev(int fd, struct iovec *iov, int iovcnt) {
    std::vector<char> data;
    for (int i = 0; i < iovcnt; i++) {
        char *begin = (char *)iov[i].iov_base;
        data.insert(data.end(), begin, begin + iov[i].iov_len);
    }

    return write(fd, &data[0], data.size());
}
