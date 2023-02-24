#ifndef CISC361_BWAIT_H
#define CISC361_BWAIT_H

#include "prelude.h"

void bwait() {
    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0);
}

#endif
