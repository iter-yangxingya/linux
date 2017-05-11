// daemon app study...
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>

int daemon_init(char const* cmd) {
    // create a daemon need the following step.
    // 1. create a child process by api fork.
    // 2. create a session, become a session leader.
    // 3. change work directory to root.
    // 4. clear file mode creation mask.
    // 5. close all open file descriptor.
    // ...

    pid_t pid = fork();
    if (pid == -1) {
        // error ...
        return -1;
    }
    if (pid != 0) {
        // parent process.
        exit(0);
    }

    // option: pid == 0
    // child process.

    // create a session. become session leader.
    setsid();

    // change current work directory to root.
    chdir("/");

    // clear file mode creation mask.
    umask(0);

    // close all open file descriptor.
    close(0);
    close(1);
    close(2);

    // signal will ignore...
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        //failed...
        return -1;
    }

    int fd0 = open("/dev/null", O_RDWR);
    int fd1 = dup(0);
    int fd2 = dup(0);

    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %s", fd0, fd1, fd2);
        exit(1);
    }

    syslog(LOG_INFO, "yangxingya daemon initialize successful...\n");
    //
    return 0;
}

int main(int argc, char **argv) {
    if (daemon_init("yangxingya") == -1) {
        printf("daemon initialize failed, will exit...\n");
        return -1;
    }
    while (1) {
        sleep(1);
    }

    return 0;
}
