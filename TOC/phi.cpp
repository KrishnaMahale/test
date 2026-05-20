#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t forks[5];

void* philosopher(void* num) {

    int id = *(int*)num;

    cout << "Philosopher " << id << " is Thinking\n";

    sem_wait(&forks[id]);
    sem_wait(&forks[(id + 1) % 5]);

    cout << "Philosopher " << id << " is Eating\n";

    sem_post(&forks[id]);
    sem_post(&forks[(id + 1) % 5]);

    cout << "Philosopher " << id << " Finished Eating\n";

    return NULL;
}

int main() {

    pthread_t p[5];
    int id[5];

    for (int i = 0; i < 5; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < 5; i++) {

        id[i] = i;

        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(p[i], NULL);
    }

    return 0;
}