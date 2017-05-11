//
// \file tee.cpp
// \brief tee.cpp like tee command get stdin data to stdout and file.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>     // for getopt() function.
#include <string>
#include <vector>
#include <iostream>

#include <header.h>

int main(int argc, char *argv[]) {

    std::string usage = argv[0];
    usage += " [-a] <output file>";
    if (argc < 2 || argc > 3)
        usage_error(usage.c_str());

    int op;
    bool append = false;
    std::string output = argv[argc - 1];
    if (argc == 3) {
        while ((op = getopt(argc, argv, "a")) != -1) {
            switch (op) {
                case 'a':
                    append = true;
                    if (optind == 3)
                        output = argv[1];
                    break;
                default:
                    std::cout << "invalid argument option" << std::endl;
                    usage_error(usage.c_str());
                    break;
            }
        }
    }

    int flags = O_CREAT | O_WRONLY | (append ? O_APPEND : O_TRUNC);
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    int ofd;
    if ((ofd = open(output.c_str(), flags, mode)) == -1)
        error_exit("open");

    ssize_t len;
    std::vector<char> buf(1024);
    std::string line;
    while ((len = read(STDIN_FILENO, &buf[0], buf.size() - 1)) != -1) {
        buf[len] = '\0';
        line += &buf[0];
        if (buf[len - 1] == '\n') {
            if (write(ofd, line.c_str(), line.length()) != (ssize_t)line.length())
                error_exit("write");
            std::cout << line;
            line = "";
        }
    }
    std::cout << "out ..." << std::endl;

    close(ofd);
    return 0;
}

