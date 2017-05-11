//
// \file atomic_append.cpp
// \brief atomic append file with O_APPEND or not test by multi-thread.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <header.h>

int main(int argc, char *argv[]) {
    std::string usage = argv[0];
    usage += " <file> <num-bytes> [x]";
    if (argc == 2) {
        std::string arg = argv[1];
        if (arg != "--help" && arg != "-h") {
            std::cout << "Invalid argument" << std::endl;
        }
        usage_error(usage.c_str());
    }

    std::string file;
    int bytes = 0;
    bool append = true;
    if (argc >= 3) {
        file = argv[1];
        bytes = to_int(argv[2], any_base, argv[2]);
        if (argc >= 4 && argv[3][0] == 'x')
            append = false;
    }

    if (file.empty()) {
        std::cout << "Invalid argument" << std::endl;
        usage_error(usage.c_str());
    }

    // check file if exist and create.
    int fd;
    int flags = O_RDWR | O_CREAT | O_EXCL;
    if (append)
        flags |= O_APPEND;
    mode_t mode = S_IRUSR | S_IWUSR;
    if ((fd = open(file.c_str(), flags, mode)) == -1) {
        //file exist.
        flags = O_RDWR;
        if (append)
            flags |= O_APPEND;
        if ((fd = open(file.c_str(), flags)) == -1)
            error_exit("open");
    }

    char byte = '0';
    ssize_t len = 1;
    while (bytes > 0) {
        if (!append) {
            if (lseek(fd, 0, SEEK_END) == -1)
                error_exit("lseek");
        }

        if (write(fd, &byte, len) != len)
            error_exit("write");

        bytes--;
    }

    close(fd);

    return 0;
}
