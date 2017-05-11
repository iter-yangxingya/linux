//
// \file seek_io.cpp
// \brief seek_io.cpp for seek offset read/write data/string.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>      // for isprint(int char); function.
#include <string>
#include <iostream>
#include <vector>

#include <header.h>

int main(int argc, char *argv[]) {

    std::string usage = argv[0];
    usage += " file {r<length>|R<length>|w<string>|s<offset>}...\n";

    if (argc == 2) {
        std::string argv1 = argv[1];
        if (argv1 == "--help" || argv1 == "-h")
            usage_error(usage.c_str());
    }

    if (argc >= 3) {
        int fd;
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
        if ((fd = open(argv[1], O_CREAT | O_RDWR, mode)) == -1)
            error_exit("open");

        bool has_offset = false;
        bool read_op = false;
        std::string rlength;
        bool show_str = false;
        std::string wstr;
        std::string soffset;
        for (int ap = 2; ap < argc; ap++) {
            switch(argv[ap][0]) {
                case 'r':
                    read_op = true;
                    show_str = true;
                    rlength = argv[ap];
                    break;
                case 'R':
                    read_op = true;
                    show_str = false;
                    rlength = argv[ap];
                    break;
                case 'w':
                    read_op = false;
                    wstr = argv[ap];
                    break;
                case 's':
                    has_offset = true;
                    soffset = argv[ap];
                    break;
                default:
                    usage_error(usage.c_str());
            }
        }
        if (has_offset) {
            off_t offset = to_long(soffset.substr(1).c_str(), any_base, soffset.c_str());
            if (lseek(fd, offset, SEEK_SET) == -1)
                error_exit("lseek");
        }

        if (read_op) {
            size_t len = to_long(rlength.substr(1).c_str(), any_base, rlength.c_str());
            std::vector<char> buff(len);
            ssize_t rlen = read(fd, &buff[0], buff.size());
            if (rlen == -1)
                error_exit("read");
            if (rlen == 0) {
                std::cout << rlength << " end of file" << std::endl;
                return -1;
            }
            std::cout << rlength << ":";
            for (int i = 0; i < rlen; i++) {
                if (i % 10 == 0) {
                    if (show_str){
                        if (i % 40 == 0)
                            std::cout << std::endl;
                    } else
                        std::cout << std::endl;
                }
                if (show_str)
                    std::cout << (isprint((unsigned char)buff[i]) ? buff[i] : '?');
                else
                    printf("%02x ", (unsigned int)buff[i]);

            }
            std::cout << std::endl;
        } else {
            if (wstr.empty())
                usage_error(usage.c_str());

            int wlen;
            if ((wlen = write(fd, wstr.substr(1).c_str(), wstr.length() - 1)) == -1)
                error_exit("write");

            std::cout << wstr << ": wrote " << wlen << " bytes" << std::endl;
        }
        close(fd);
        return 0;
    }
    std::cout << "invalid argument..." << std::endl;
    usage_error(usage.c_str());
    return -1;
}
