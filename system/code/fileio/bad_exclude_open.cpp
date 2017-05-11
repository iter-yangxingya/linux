//
// \file bad_exclude_open.cpp
// \brief bad_exclude_open.cpp for check file exist and create file by two steps
//      when multi-process/thread will be a problem.

#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <header.h>

// getpid() system call at <unistd.h> and <sys/stat.h>
// sleep() system call at <unistd.h>, you can call "man 3 sleep" for search.

int main(int argc, char *argv[]) {
    std::string usage = argv[0];
    usage += " <file> [sleep seconds]";
    int seconds = 0;
    std::string file;
    if (argc >= 2) {
        std::string argv1 = argv[1];
        if (argv1 == "--help" || argv1 == "-h")
            usage_error(usage.c_str());
        file = argv1;
        if (argc >= 3 )
            seconds = to_int(argv[2], any_base, argv[2]);
    }

    // step 1: check file is existed.
    int fd = open(file.c_str(), O_WRONLY);
    if (fd != -1) {
        std::cout << "[PID " << getpid() << "] File " << file << " already exists"
            << std::endl;
        close(fd);
    } else {
        if (errno != ENOENT) {
            error_exit("open");
        } else {
            // sleep or not?
            if (seconds > 0)
                sleep(seconds);

            // step 2: create file when file is not existed.
            int flags = O_WRONLY | O_CREAT;
            mode_t mode = S_IRUSR | S_IWUSR;
            if ((fd = open(file.c_str(), flags, mode)) == -1)
                error_exit("open");

            std::cout << "[PID " << getpid() << "] Created File " << file
                << " exclusively" << std::endl;
        }
    }
    return 0;
}
