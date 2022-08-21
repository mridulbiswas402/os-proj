#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "buffer.h" 
#include "buffer.c" //implementation of a queue.

void *producer(void *params);
void *consumer(void *params);

Queue Q; // shared queue between producer and consumer.
pthread_mutex_t mutex; // mutex lock declaration.

int main(int argc,char *argv[]){

    Queue_init(&Q); //initializing queue.
    pthread_mutex_init(&mutex,NULL); // initializing mutex lock.

    pthread_t tid1,tid2; // thread identifiers.
    pthread_attr_t attr; // set of thread attributes.

    pthread_attr_init(&attr); // initializing threads default attribute.

    /*creating thread and assigning task.*/
    pthread_create(&tid1,&attr,producer,NULL);
    pthread_create(&tid1,&attr,consumer,NULL);

    sleep(atoi(argv[1])); // the main thread is sleeping.
    exit(0);
}

void *producer(void *params){
    while(1){
        item val=rand()%100; // producing a random item.

        pthread_mutex_lock(&mutex); // entry section
        /* critical section */
        insert(&Q,val);
        printf("%d produced & buff size is %d\n",val,Q.size);

        pthread_mutex_unlock(&mutex); // exit section.
        sleep(1); // reminder section.
    }
}

void *consumer(void *params){
    while(1){
        pthread_mutex_lock(&mutex); // entry section.
        /* critical section */
        item x=remove_item(&Q); // consuming item.
        printf("%d consumed & buff size is %d\n",x,Q.size);

        pthread_mutex_unlock(&mutex); // exit section.
        sleep(1); // reminder section.
    }
}