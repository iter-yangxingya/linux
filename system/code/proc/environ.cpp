//
// \file environ.cpp
// \brief environ.cpp for implement setenv()/unsetenv() with getenv()/putenv() function.
//

#include <stdlib.h>
#include <iostream>
#include <header.h>

extern char **environ;

int i_setenv(const char *name, const char *value, int overwrite);
int i_unsetenv(const char *name);
void print_env();

int main(/*int argc, char *argv[]*/) {
    clearenv();
    // raw api setenv()/unsetenv().
    std::cout << "raw api setenv()/unsetenv() call begin ===>" << std::endl;

    char name[] = "SHELL";
    char value[] = "/bin/sh";
    char value2[] = "/bin/bash";

    char const *hello = "SHELL=hello";
    char const *world = "SHELL=world";
    int hlen = strlen(hello);
    int wlen = strlen(world);
    char *v1;
    char *v2;
    if ((v1 = (char *)malloc(hlen + 1)) == nullptr)
        error_exit("malloc");
    strcpy(v1, hello);
    v1[hlen] = '\0';

    if ((v2 = (char *)malloc(wlen + 1)) == nullptr)
        error_exit("malloc");
    strcpy(v2, world);
    v2[wlen] = '\0';

    if (setenv(name, value, 0) == -1)
        error_exit("setenv");
    std::cout << "call setenv(" << name << ", " << value << ", 0) succeed" << std::endl;
    print_env();

    if (setenv(name, value, 0) == -1)
        error_exit("setenv");
    std::cout << "call setenv(" << name << ", " << value << ", 0) twice succeed" << std::endl;
    print_env();

    if (setenv(name, value2, 1) == -1)
        error_exit("setenv");
    std::cout << "call setenv(" << name << ", " << value2 << ", 1) succeed" << std::endl;
    print_env();

    // the fowllowing putenv() call twince no add twince SHELL=... environment, but once, the las
    // modify the first content to last value.
    // ??? who tell me how to make more than one the same name <name>=<value> pair???
    // to validate the i_unsetenv()'s implement???

    if (putenv(v1) != 0)
        error_exit("putenv");
    std::cout << "call putenv(" << v1 << ") succeed" << std::endl;
    print_env();

    if (putenv(v2) != 0)
        error_exit("putenv");
    std::cout << "call putenv(" << v2 << ") succeed" << std::endl;
    print_env();

    if (unsetenv(name) == -1)
        error_exit("i_unsetenv");
    std::cout << "call unsetenv(" << name << ") succeed" << std::endl;
    print_env();

    std::cout << "raw api setenv()/unsetenv() call end <===" << std::endl;

    clearenv();

    std::cout << "implement api setenv()/unsetenv() call begin ===>" << std::endl;
    if (i_setenv(name, value, 0) == -1)
        error_exit("i_setenv");
    std::cout << "call setenv(" << name << ", " << value << ", 0) succeed" << std::endl;
    print_env();

    if (i_setenv(name, value, 0) == -1)
        error_exit("setenv");
    std::cout << "call setenv(" << name << ", " << value << ", 0) twice succeed" << std::endl;
    print_env();

    if (i_setenv(name, value2, 1) == -1)
        error_exit("setenv");
    std::cout << "call setenv(" << name << ", " << value2 << ", 1) succeed" << std::endl;
    print_env();

    if (i_unsetenv(name) == -1)
        error_exit("i_unsetenv");
    std::cout << "call unsetenv(" << name << ") succeed" << std::endl;
    print_env();

    std::cout << "implement api setenv()/unsetenv() call end <===" << std::endl;
    return 0;
}

int i_setenv(const char *name, const char *value, int overwrite) {
    if (name == nullptr)
        return -1;

    int nlen = strlen(name);
    int vlen = strlen(value);
    char *env;
    if ((env = (char *)malloc(nlen + vlen + 2)) == nullptr)
        return -1;

    strcpy(env, name);
    env[nlen] = '\0';

    // 1. if name is existed and overwrite is zero, do nothing return 0.
    char *v;
    if ((v = getenv(name)) != nullptr) {
        if (!overwrite)
            return 0;

        // overwrite == 1
        if (strcmp(v, value) == 0)
            return 0;
        // v != value.
        // 1. first clear the old name=value pair
        //  the following use glibc extand...
        if (putenv(env) != 0)
            return -1;
    }

    // 2. name is not exist.
    //  make name=pair format.
    strcpy(env + nlen, "=");
    strcpy(env + nlen + 1, value);
    env[nlen + vlen + 1] = '\0';

    if (putenv(env) != 0)
        return -1;

    return 0;
}

int i_unsetenv(const char *name) {
    if (name == nullptr)
        return -1;

    int len = strlen(name);
    char *env;
    if ((env = (char *)malloc(len)) == nullptr)
        return -1;

    strcpy(env, name);
    env[len] = '\0';

    char *v;
    while ((v = getenv(name)) != nullptr) {
        if (putenv(env) != 0)
            return -1;
    }
    return 0;
}

void print_env() {
    if (environ == nullptr) {
        std::cout << "environ is nullptr..." << std::endl;
        return;
    }

    for (char **ep = environ; *ep != nullptr; ep++)
        std::cout << *ep << std::endl;
}
