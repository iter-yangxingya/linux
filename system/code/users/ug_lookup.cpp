//
// \file ug_lookup.cpp
// \brief user and group id from name to id or from id to name convert.
//

#include <pwd.h>    // getpwnam()/getpwuid()
#include <grp.h>    // getgrnam()/getgrgid()
#include "ug_lookup.h"

std::string uid_to_name(uid_t id) {
    struct passwd *pwd;
    if ((pwd = getpwuid(id)) == nullptr)
        return std::string("");
    return std::string(pwd->pw_name);
}

uid_t uname_to_id(std::string const& name) {
    if (name.empty())
        return -1;

    uid_t id;
    size_t pos;
    try {
        id = std::stol(name, &pos);
        if (name[pos] == '\0')
            return id;
    } catch (...) {

    }

    struct passwd *pwd;
    if ((pwd = getpwnam(name.c_str())) == nullptr)
        return -1;

    return pwd->pw_uid;
}

std::string gid_to_name(gid_t id) {
    struct group *grp;
    if ((grp = getgrgid(id)) == nullptr)
        return std::string("");

    return std::string(grp->gr_name);
}

gid_t gname_to_id(std::string const& name) {
    if (name.empty())
        return -1;

    gid_t id;
    size_t pos;
    try {
        id = std::stol(name, &pos);
        if (name[pos] == '\0')
            return id;
    } catch (...) {

    }

    struct group *grp;
    if ((grp = getgrnam(name.c_str())) == nullptr)
        return -1;

    return grp->gr_gid;
}
