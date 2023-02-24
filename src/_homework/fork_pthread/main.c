#include <common.h>

int value = 0;

static void* runner(void* param);

int main() {
    pid_t pid;
    pthread_t tid;

    pid = fork();
    if (!pid) {
        pthread_create(&tid, NULL, &runner, NULL);
        pthread_join(tid, NULL);
        printf("CHILD: value = %d\n", value);
    } else {
        wait(NULL);
        printf("PARENT: value = %d\n", value);
    }

    return 0;
}

static void* runner(void* param) {
    value = 5;
    pthread_exit(0);
}
