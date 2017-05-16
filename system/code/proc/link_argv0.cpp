//
// \file link_argv0.cpp
// \brief link_argv0.cpp for argv[0] when make a softlink, but name will be
//      different.
//

#include <iostream>
#include <string>
#include <header.h>

#if !defined(_GNU_SOURCE) // gcc will include the MACRO default.
# define _GNU_SOURCE
#endif
#include <errno.h>

// use file /proc/<PID>/cmdline to get the command line.
// use file /proc/self/cmdline to get my own command line.

// gun c library have two global variable.
//  1. program_invocation_name: full app path: only the caller input full path,
//     if you input './app' will be './app' not be a absolute path.
//  2. program_invocation_short_name: short name, no with directory.
// NOTICE:
// the two way will match softlink principle.

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++)
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;

    std::cout << "full app name: " << program_invocation_name << std::endl;
    std::cout << "short app name: " << program_invocation_short_name << std::endl;

    return 0;
}

// you can use the following make a soft-link.
//      $ ln -s <bin-file> <link-file>
// for example bin file is 'link_argv', link file is 'newbi'
// execute ls -al can find newbi is a link of link_argv.
// but execute the following will be different.
//      $ ./link_argv
//      $ argv[0] = ./link_argv
//      $ ./newbi
//      $ argv[0] = ./newbi
// you can use this feature do different things.
// the following is the example of it:
//  gzip/gunzip/zcat...
//
