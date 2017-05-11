//
// \file copy_ex.cpp
// \brief copy_ex.cpp for copy improve, only copy has data part.
//

#include <sys/stat.h>
#include <fcntl.h>

#include <string>
#include <vector>
#include <iostream>

#include <header.h>

int main(int argc, char *argv[]) {
    std::string usage = argv[0];
    usage += " <old-file> <new-file>";

    if (argc == 2) {
        std::string argv1 = argv[1];
        if (argv1 == "--help" || argv1 == "-h")
            usage_error(usage.c_str());
    }

    if (argc != 3) {
        std::cout << "invalid argument..." << std::endl;
        usage_error(usage.c_str());
    }

    int ifd;
    if ((ifd = open(argv[1], O_RDONLY)) == -1)
        error_exit("open");

    int flags = O_CREAT | O_WRONLY | O_TRUNC;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int ofd;
    if ((ofd = open(argv[2], flags, mode)) == -1)
        error_exit("open");

    std::vector<char> nul(1024);
    std::vector<char> buf(1024);
    off_t offset = 0;
    ssize_t len;

    while ((len = read(ifd, &buf[0], buf.size())) > 0) {
        if (memcmp(&buf[0], &nul[0], len) != 0) {
            std::cout << "offset: " << offset << std::endl;
            if (lseek(ofd, offset, SEEK_SET) == -1)
                error_exit("lseek");

            if (write(ofd, &buf[0], len) != len)
                error_exit("write");
        }
        offset += len;
    }

    if (len == -1)
        error_exit("read");

    if (close(ifd) == -1)
        error_exit("close");
    if (close(ofd) == -1)
        error_exit("close");

    return 0;
}
