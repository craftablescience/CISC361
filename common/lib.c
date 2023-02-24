#include <common.h>

void bwait() {
    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0);
}
