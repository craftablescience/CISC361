#include <common.h>

sem_t mutex;
int count = 0;

#define MAX_NO_OF_THREADS 4
#define MAX_TIMES_TO_INCREMENT 5

typedef struct {
    int thread_number;
} arg_data;

void* thread_worker(void* arg) {
    arg_data* current_thread_data = (arg_data*) arg;

    sem_wait(&mutex);

    // start of critical section
    printf("\nThread %d entering critical section...\n", current_thread_data->thread_number);
    int local_count = count;
    for (int i = 0; i < MAX_TIMES_TO_INCREMENT; i++) {
        local_count++;
        printf("\nThread %d Value: %d\n", current_thread_data->thread_number, local_count);
    }
    count = local_count;
    printf("\nThread %d exiting critical section...\n", current_thread_data->thread_number);
    // end of critical section

    sem_post(&mutex);

    return NULL;
}

int main() {
    // pthread objects
    pthread_t id[MAX_NO_OF_THREADS];

    // argument data to send in worker functions
    arg_data arg_arr[MAX_NO_OF_THREADS];

    // init semaphore
    sem_init(&mutex, 0, 1);

    // total number of threads we will create
    int no_of_threads = MAX_NO_OF_THREADS;
    printf("Creating %d threads...\n", no_of_threads);

    // creating the child threads
    for (int thread_no = 0; thread_no < MAX_NO_OF_THREADS; thread_no++) {
        arg_arr[thread_no].thread_number = thread_no + 1;
        pthread_create(&id[thread_no], NULL, thread_worker, &arg_arr[thread_no]);
    }

    // joining the threads one by one
    for (int i = 0; i < MAX_NO_OF_THREADS; i++) {
        pthread_join(id[i], NULL);
    }

    // close semaphore
    sem_destroy(&mutex);

    // check
    if (count != MAX_TIMES_TO_INCREMENT * MAX_NO_OF_THREADS) {
        printf("Value Incorrect! count = %d\n", count);
    } else {
        printf("Value Correct! count = %d\n", count);
    }
}
