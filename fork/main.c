#include <common.h>

/*
 * Print these in the following order:
 * I am the grandchild (#), where ‘#’ is the pid of the grandchild process
 * I am the child (#), where ‘#’ is the pid of the child process
 * I am the parent (#), where ‘#’ is the pid of the parent process
 */
int main() {
    pid_t child = fork();
    if (!child) {
        pid_t grandchild = fork();
        if (!grandchild) {
            printf("I am the grandchild (%d)\n", getpid());
            exit(0);
        } else {
            bwait();
            printf("I am the child (%d)\n", getpid());
            exit(0);
        }
    } else {
        bwait();
        printf("I am the parent (%d)\n", getpid());
    }

    return 0;
}
