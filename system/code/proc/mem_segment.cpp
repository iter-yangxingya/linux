//
// \file mem_segment.cpp
// \brief mem_segment.cpp for memory segment of application.
//

#include <iostream>

char global_buf[65536];
int primes[] = {2, 3, 5, 7};

static int square(int x) {  // x will in stack frame.
    int result;             // result will be in stack frame.
    result = x * x;
    return result;          // return value pass by resister.
}

static void do_calc(int val) {
    std::cout << "the square of " << val << " is " << square(val) << std::endl;

    if (val < 1000) {
        int t;              // stack frame.
        t = val * val * val;
        std::cout << "the cube of " << val << " is " << t << std::endl;
    }
}

int main(/*int argc, char *argv[]*/) {
    static int key = 9973;      // initialized data segment.
    static char mbuf[10240000]; // un-intialized data segment.
    char *p;          // stack frame.

    // the following is c synatx
    // p = malloc(1024);        // heap segment.
    // the following is c++ synatx
    p = (char *)malloc(1024);   // heap segment.

    do_calc(key);

    mbuf[0] = '\0';

    return 0;
}

// global variable global_buf will be NOT use binary file size, because it is a
//  un-initialized data segment(bss segment).
// likely:
// static variable mbuf is also NOT use binary file size, it is record the position
//  and size of the variable, it will be calc at run-time and when app loader will
//  allocate it's space.
//
// you can use the following command line for check the size of binary.
//  $ ls -al <binary-file>
// it will be less than mbuf's size.
