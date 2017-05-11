//
// \file copy.cpp
// \brief for copy existing file to new file.
//

#include <sys/stat.h>   // for ???
#include <fcntl.h>      // for ???
#include <header.h>     // for my own error wrapper function.
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        std::string argv1 = argv[1];
        if (argv1 == "--help" || argv1 == "-h")
            usage_error("%s old-file new-file\n", argv[0]);
    }

    if (argc != 3) {
        std::cout << "Invalid argument" << std::endl;
        usage_error("%s old-file new-file\n", argv[0]);
    }

    int src_fd;
    if ((src_fd = open(argv[1], O_RDONLY)) == -1)
        error_exit("open file %s", argv[1]);

    int flags = O_CREAT | O_WRONLY | O_TRUNC;
    // rw-rw-rw-
    mode_t perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    int dst_fd;
    if ((dst_fd = open(argv[2], flags, perms)) == -1)
        error_exit("open file %s", argv[2]);

    ssize_t len;
    char buf[1024];
    while ((len = read(src_fd, buf, sizeof(buf))) > 0)
        if (write(dst_fd, buf, len) != len)
            fatal("couldn't write whole buffer");

    if (len == -1)
        error_exit("read");

    if (close(src_fd) == -1)
        error_exit("close source");
    if (close(dst_fd) == -1)
        error_exit("close destination");

    exit(EXIT_SUCCESS);
}
