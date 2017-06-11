//
// \file ug_lookup.h
// \brief user & group name & id converte.
//

#if !defined(ug_lookup_h__)
#define ug_lookup_h__

#include <string>

// user name & id converte.
std::string uid_to_name(uid_t id);
uid_t uname_to_id(std::string const& name);

// group name & id converte.
std::string gid_to_name(gid_t id);
gid_t gname_to_id(std::string const& name);

#endif // ug_lookup_h__
