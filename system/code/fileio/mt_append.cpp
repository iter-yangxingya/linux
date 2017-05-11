//
// \file mt_append.cpp
// \brief mt_append.cpp for multi-thread/process append a file.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <thread>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <header.h>

int main(int argc, char *argv[]) {
    std::string usage = argv[0];
    usage += " <thread count>";

    if (argc != 2)
        usage_error(usage.c_str());

    // argc == 2
    std::string arg = argv[1];
    if (arg == "--help" || arg == "-h")
        usage_error(usage.c_str());

    int count = to_int(arg.c_str(), any_base, arg.c_str());

    std::string file = argv[0];
    file += ".txt";
    int fd;
    int flags = O_CREAT | O_TRUNC | O_APPEND | O_WRONLY;
    mode_t mode = S_IRUSR | S_IWUSR;
    if ((fd = open(file.c_str(), flags, mode)) == -1)
        error_exit("open");

    auto append_func = [](int fd, int index, int times) {
        std::string content = std::to_string(index);
        content += ": [TID ";
        //content += std::to_string(gettid());
        //content += std::to_string(std::this_thread::get_id());
        content += "] ";
        for (int i = 0; i < 10; i++)
            content += ('A' + (index * 5) % 26 + i);
        content += "\n";
        for (int i = 0; i < times; i++) {
            if (lseek(fd, SEEK_END, 0) == -1)
                error_exit("lseek");
            if (write(fd, content.c_str(), content.length()) != (ssize_t)content.length())
                error_exit("write");
        }
    };

    std::vector<std::shared_ptr<std::thread>> threads;
    for (int i = 0; i < count; i++) {
        threads.emplace_back(std::shared_ptr<std::thread>(
            new std::thread(append_func, fd, i, 300)));
    }

    for (int i = 0; i < count; i++) {
        std::shared_ptr<std::thread> thread = threads[i];
        if (thread->joinable())
            thread->join();
    }

    std::cout << "all over..." << std::endl;
    return 0;
}
