//
// \file temp_file.cpp
// \brief temp_file.cpp for temp file create api: mkstemp()/tmpfile()
//

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>     // for mkstemp() api
#include <stdio.h>      // for tmpfile() api
#include <string>
#include <vector>
#include <iostream>
#include <header.h>

void api_mkstemp();
void api_tmpfile();
int main() {
    api_mkstemp();
    api_tmpfile();
    return 0;
}

void api_mkstemp() {
    std::vector<char> temp(64);
    char *file = &temp[0];
    strcpy(file, "./mkstemp-XXXXXX");
    // mkstemp() api argument must end with 'XXXXXX' for temp.
    int fd;

    // mkstemp() api detail:
    //  1. flags == O_RDWR | O_CREAT | O_EXCL(exclude)
    //  2. mode == S_IRUSR | S_IWUSR == -rw-------
    //  3. filename is random by template file replace XXXXXX.
    //  4. mktemp()/tmpnam()/tempnam() has the security problem, so suggest
    //     use mkstemp().
    if ((fd = mkstemp(file)) == -1)
        error_exit("mkstemp");
    // what's access mode??? O_RDONLY/O_WRONLY/O_RDWR???

    std::cout << "generate temp file name: " << file << std::endl;

    std::cout << "file create..." << std::endl;
    std::cout << "wait you input to continue..." << std::endl;
    int x;
    std::cin >> x;

    // unlink() call after:
    //  1. file disappears immediately,
    //  2. but the file is removed when call close() api.
    //  3. you can do you own call likely read/write operate.
    unlink(file);

    std::cout << "unlink the file, the file should be disappeared." << std::endl;
    std::cout << "wait you input to continue..." << std::endl;
    std::cin >> x;

    int value = 0x11223344;
    ssize_t len = (ssize_t)sizeof(value);
    if (write(fd, &value, len) != len)
        error_exit("write");

    std::cout << "temp file has WRITE access." << std::endl;

    int data;
    off_t off = 0;
    if (pread(fd, &data, len, off) != len)
        error_exit("pread");

    std::cout << "temp file has READ access." << std::endl;

    if (close(fd) == -1)
        error_exit("close");
}

void api_tmpfile() {
    FILE *file;

    // tmpfile() api detail:
    //  1. create file with O_RDWR | O_CREAT | O_EXCL;
    //  2. mode is S_IRUSR | S_IWUSR???
    //  3. create succeed, can't see the file, because call tmpfile() will call
    //     unlink() api to disappear the file.
    //  4. close the file descriptor will remove the file. process exit will
    //     close all opened descriptor. so process exit the temp file removed.
    if ((file = tmpfile()) == nullptr)
        error_exit("tmpfile");

    // read/write. by stdio api like: fread()/fwrite()/fseek()...

    // close the file by stdio.h api fclose()
    fclose(file);
}
