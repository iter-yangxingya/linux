//
// \file spec_off_rw.cpp
// \brief spec_off_rw.cpp for pread()/pwrite() api example, they read/write file
//      at special offset at atomiclly, no modify file read/write offset.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <header.h>

int main() {
    // 1. get file offset.
    std::string file = "sop";
    int fd;
    int flags = O_CREAT | O_TRUNC | O_RDWR;
    mode_t mode = S_IRUSR | S_IWUSR;
    if ((fd = open(file.c_str(), flags, mode)) == -1)
        error_exit("open");

    // write.
    off_t off;
    if ((off = lseek(fd, 0, SEEK_CUR)) == -1)
        error_exit("lseek");

    std::cout << "---> offset: " << off << std::endl;
    int value = 0x12345678;
    size_t wlen = sizeof(value);
    off_t woff = 1 << 20;
    if (pwrite(fd,  &value, wlen, woff) != (ssize_t)wlen)
        error_exit("pwrite");

    std::cout << "write offset: " << woff << ", value=" << value << " over" << std::endl;
    if ((off = lseek(fd, 0, SEEK_CUR)) == -1)
        error_exit("lseek");

    std::cout << "<--- offset: " << off << std::endl;

    // read.
    if ((off = lseek(fd, 0, SEEK_CUR)) == -1)
        error_exit("lseek");

    std::cout << "---> offset: " << off << std::endl;
    int data;
    size_t rlen = sizeof(data);
    if (pread(fd, &data, rlen, woff) != (ssize_t)rlen)
        error_exit("pread");

    std::cout << "read offset: " << woff << ", value=" << data <<  " over" << std::endl;
    if ((off = lseek(fd, 0, SEEK_CUR)) == -1)
        error_exit("lseek");

    std::cout << "<--- offset: " << off << std::endl;

    close(fd);
    return 0;
}
