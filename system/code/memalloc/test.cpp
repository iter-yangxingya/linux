//
// \file test.cpp
// \brief test.cpp for test malloc.h define i_malloc()/i_free();
//

#include <iostream>
#include <string>
#include <malloc.h>
#include <header.h>

int main() {
    char *pa;
    if ((pa = (char *)i_malloc(1000)) == nullptr)
        std::cout << "i_malloc(1000) failed." << std::endl;
    else
        std::cout << "i_malloc(1000) succeed." << std::endl;

    memset(pa, 1, 1000);

    i_free(pa);
    std::cout << "i_free() over..." << std::endl;

    if ((pa = (char *)i_malloc(1024000)) == nullptr)
        std::cout << "i_malloc(1024000) failed." << std::endl;
    else
        std::cout << "i_malloc(1024000) succeed." << std::endl;

    memset(pa, 2, 1024000);

    i_free(pa);
    std::cout << "i_free() over..." << std::endl;

    return 0;
}
