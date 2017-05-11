//
// \file min_fd.cpp
// \brief min_fd.cpp for SUSv3 standard: fd must be the min number of no usage
//      of this process.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <header.h>

int main() {
    // close the stdin file descriptor.
    if (close(STDIN_FILENO) == -1)
        error_exit("close");

    // create new file.
    int fd;
    if ((fd = open("./minfd", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR)) == -1)
        error_exit("open");

    std::cout << "close STDIN, and open ./minfd file descriptor is: " << fd << std::endl;
    write(fd, &fd, sizeof(fd));

    if (close(fd) == -1)
        error_exit("close2");

    exit(EXIT_SUCCESS);
}
