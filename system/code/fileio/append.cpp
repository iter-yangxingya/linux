//
// \file append.cpp
// \brief append.cpp for append flags and seek from header.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <iostream>
#include <header.h>

int main(int argc, char *argv[]) {
    std::string usage = argv[0];
    usage += " <file>";
    if (argc != 2) {
        std::cout << "Invalid argument" << std::endl;
        usage_error(usage.c_str());
    }

    // argc == 2.
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help")
        usage_error(usage.c_str());

    int fd;
    int flags = O_RDWR | O_CREAT | O_EXCL | O_APPEND;
    mode_t mode = S_IRUSR | S_IWUSR;
    if ((fd = open(arg.c_str(), flags, mode)) == -1) {
        std::cout << "file: " << arg << " is existed, will open it" << std::endl;
        flags = O_RDWR | O_TRUNC | O_APPEND;
        if ((fd = open(arg.c_str(), flags)) == -1)
            error_exit("open");
    }

    off_t begin = lseek(fd, 0, SEEK_CUR);
    std::cout << "file open over, r/w offset pointer is: " << begin << std::endl;

    // 1. first fill data to file.
    std::string data = "abcdefghihklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    ssize_t dlen = (ssize_t)data.length();
    if (write(fd, data.c_str(), dlen) != dlen)
        error_exit("write");

    std::cout << "fill file offset[0] data: " << data << std::endl;

    close(fd);
    std::cout << "close file......" << std::endl;
    std::cout << std::endl;

    flags = O_RDWR | O_APPEND;
    if ((fd = open(arg.c_str(), flags)) == -1)
        error_exit("open");

    std::cout << "re-open file: " << arg << " succeed" << std::endl;

    off_t off = 0;
    off_t pos;
    if ((pos = lseek(fd, off, SEEK_SET)) == -1)
        error_exit("lseek");

    std::cout << "seek begin[" << off << "] return: " << pos << std::endl;

    // when seek to begin, write data...
    data = "###%%%%%%%###";
    dlen = (ssize_t)data.length();
    if (write(fd, data.c_str(), dlen) != dlen)
        error_exit("write");

    std::cout << "write to file offset[0] data: " << data << std::endl;

    // seek to begin.
    off = 0;
    if ((pos = lseek(fd, off, SEEK_SET)) == -1)
        error_exit("lseek");

    std::cout << "seek begin[" << off << "] return: " << pos << std::endl;

    // read begin.
    std::vector<char> buf(16);
    ssize_t blen = (ssize_t)buf.size() - 1;
    ssize_t rlen;
    if ((rlen = read(fd, &buf[0], blen)) < 0)
        error_exit("read");

    buf[rlen] = '\0';
    std::cout << "read from begin offset[0] data: " << &buf[0] << std::endl;

    // read end, first need seek end - dlen.
    off = 0 - blen;
    if ((pos = lseek(fd, off, SEEK_END)) == -1)
        error_exit("lseek");

    std::cout << "seek begin[" << off << "] return: " << pos << std::endl;

    if ((rlen = read(fd, &buf[0], blen)) < 0)
        error_exit("read");

    buf[rlen] = '\0';
    std::cout << "read from end offset[" << pos << "] data: " << &buf[0] << std::endl;

    close(fd);
    return 0;
}
