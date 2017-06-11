//
// \file scan_passwd.cpp
// \brief scan passwd every line info by step.
//
// \note: getpwent() read one line and set file pointer to next line.
//        setpwent() set read pointer to first line.
//        endpwent() close the password file pointer.

#include <pwd.h>    // getpwent()/setpwent()/endpwent()
#include <stdio.h>

int main() {
    struct passwd *pwd;
    while ((pwd = getpwent()) != nullptr) {
        printf("%-20s %5ld\n", pwd->pw_name, (long)pwd->pw_uid);
    }

    endpwent();

    return 0;
}
