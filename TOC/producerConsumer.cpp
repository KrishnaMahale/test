#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t emptySlots, fullSlots, mutex;

int buffer = 0;

void* producer(void* arg) {

    for (int i = 1; i <= 5; i++) {

        sem_wait(&emptySlots);
        sem_wait(&mutex);

        buffer++;

        cout << "Produced Item " << buffer << endl;

        sem_post(&mutex);
        sem_post(&fullSlots);
    }

    return NULL;
}

void* consumer(void* arg) {

    for (int i = 1; i <= 5; i++) {

        sem_wait(&fullSlots);
        sem_wait(&mutex);

        cout << "Consumed Item " << buffer << endl;

        buffer--;

        sem_post(&mutex);
        sem_post(&emptySlots);
    }

    return NULL;
}

int main() {

    pthread_t p, c;

    sem_init(&emptySlots, 0, 5);
    sem_init(&fullSlots, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}