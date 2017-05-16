//
// \file sbrk.cpp
// \brief sbrk.cpp for brk()/sbrk() system call, it is SUSv2, SUSv3 delete the defination.
//

#include <unistd.h>     // for brk()/sbrk()
// API define:
//  int brk(void *end_data_segment);
//  void *sbrk(intptr_t increment);
// generally, use sbrk(), heap memory start will be equal as 'end' define UN-initialized
// data segment tail(bss segment tail.)
// you can use sbrk(0) to get the value.

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>     // for malloc()/free().
#include <header.h>

#define MAX_ALLOCS 1000000

int main(int argc, char *argv[]) {
    std::string usage = argv[0];
    usage += " num-allocs block-size [step [min [max]]]";
    if (argc <= 2) {
        std::string argv1;
        if (argc == 2) argv1 = argv[1];
        if (argv1 != "--help" && argv1 != "-h")
            std::cout << "Invalid argument" << std::endl;
        usage_error(usage.c_str());
    }

    // argc >= 3.
    int allocs = to_int(argv[1], greater_zero, "num-allocs");
    if (allocs > MAX_ALLOCS)
        cmdline_error("num-alloc > %d\n", MAX_ALLOCS);

    int block_size = to_int(argv[2], greater_zero | any_base, "block-size");
    int step = (argc > 3) ? to_int(argv[3], greater_zero, "step") : 1;
    int min = (argc > 4) ? to_int(argv[4], greater_zero, "min") : 1;
    int max = (argc > 5) ? to_int(argv[5], greater_zero, "max") : allocs;

    if (max > allocs)
        cmdline_error("free-max > num-allocs\n");

    printf("initialize programm break:             %10p\n", sbrk(0));

    std::vector<void*> ptr(allocs);
    for (size_t i = 0; i < ptr.size(); i++) {
        if ((ptr[i] = malloc(block_size)) == nullptr)
            error_exit("malloc");
        printf("[%d]programm break:%10p\n", (int)i, sbrk(0));
    }

    printf("after malloc, programm break:          %10p\n", sbrk(0));

    std::cout << "freeing blocks form " << min << " to " << max << " in steps of "
        << step << std::endl;

    for (int i = min - 1; i < max; i+= step)
        free(ptr[i]);

    printf("after malloc, programm break:          %10p\n", sbrk(0));

    return 0;
}
