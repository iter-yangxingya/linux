//
// \file glibc_version.cpp
// \brief glibc_version for probe glibc version.
//

#include <iostream>
#include <gnu/libc-version.h> // for gnu_libc_version() func().
#include <unistd.h> // for confstr() func: size_t confstr(int name, char *buf, size_t len);

int main() {
    // 3 ways get glibc version.
    //1: macro __GLIBC__ & __GLIBC__MINOR__
    //2: gnu_get_libc_version() function.
    //3: confstr() function. _CS_GNU_LIBC_VERSION config.

    // 1. macro...
    std::cout << "gnu lib c version by MACRO: " << __GLIBC__ << "." << __GLIBC_MINOR__ << std::endl;

    // 2. call gnu_get_libc_version() function.
    std::cout << "gnu lib c version by gnu_get_libc_version(): " << gnu_get_libc_version() << std::endl;

    // 3. call confstr() function.
    char buf[32] = {0};
    size_t len = confstr(_CS_GNU_LIBC_VERSION, buf, sizeof(buf));
    buf[len] = 0;
    std::cout << "gnu lib c version by confstr(): " << buf << std::endl;

    return 0;
}
