#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef int item;
#define BUFFER_SIZE 100

typedef struct
{
    int front;
    int rear;
    int size;
    item buffer[BUFFER_SIZE];
} Queue;

void insert(Queue *ptr, item data);
item remove_item(Queue *ptr);
void Queue_init(Queue *ptr);
void print_state(Queue *ptr);

#endif