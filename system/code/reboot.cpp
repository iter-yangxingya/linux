//
// \file reboot.cpp
// \brief reboot api.
//

#if reboot_arg_is_3
# include <unistd.h>
# include <linux/reboot.h>   // for reboot() 3-argument sys call.
#else
# include <sys/reboot.h>     // for reboot() 1-argument wrapper 3-argument ...
#endif

#include <errno.h>
#include <iostream>

int main() {

    // int reboot(int magic, int magic2, int cmd, void *arg);

#if reboot_arg_is_3
    if (reboot(LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2C, LINUX_REBOOT_CMD_RESTART, nullptr) == 0) {
        std::cout << "reboot() call successful, will reboot ......" << std::endl;
        return 0;
    }
#else
    if (reboot(RB_AUTOBOOT) == 0) {
        std::cout << "reboot() call successful, will reboot ......" << std::endl;
        return 0;
    }
#endif //

    int error = errno;
    std::cout << "reboot() call failed, error: " << error << std::endl;
    return -1;
}

