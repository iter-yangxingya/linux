//
// \file passwd.cpp
// \brief passwd for struct passwd content.
//

#include <pwd.h>    // struct passwd
#include <iostream>
#include <string>
#include <header.h>

int main(int argc, char *argv[]) {

    std::string usage = argv[0];
    usage += " <user>";
    if (argc < 2) {
        std::cout << "Invalid usage" << std::endl;
        usage_error(usage.c_str());
        return -1;
    }

    std::string arg = argv[1];
    if (arg == "--help" || arg == "-h") {
        usage_error(usage.c_str());
        return -1;
    }

    struct passwd *pwd;
    if ((pwd = getpwnam(arg.c_str())) == nullptr) {
        std::cout << "user is not existed!" << std::endl;
        return -1;
    }

    std::cout << "user[" << arg << "]'s information:"
        << "\n\tname=" << pwd->pw_name
        << "\n\tcrypt password=" << pwd->pw_passwd
        << "\n\tuid=" << pwd->pw_uid
        << "\n\tgid=" << pwd->pw_gid
        << "\n\tuser info=" << pwd->pw_gecos
        << "\n\tinitialize work dir=" << pwd->pw_dir
        << "\n\tdefault shell=" << pwd->pw_shell
        << std::endl;

    return 0;
}
