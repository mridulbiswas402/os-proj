#include<stdio.h>
#include"queue.h"

void print_state(Queue *ptr)
{
    printf("size = %d, front = %d, rear = %d\n", ptr->size, ptr->front, ptr->rear);
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("%d,", ptr->buffer[i]);
    }
    printf("\n");
}

void Queue_init(Queue *ptr)
{
    ptr->front = 0;
    ptr->rear = 0;
    ptr->size = 0;
}

void insert(Queue *ptr, item data)
{
    // int front=ptr->front;
    // int rear=ptr->rear;
    if ((ptr->rear + 1) % BUFFER_SIZE == ptr->front)
    {
        printf("Buffer overflow\n");
        return;
    }
    else
    {
        ptr->rear = (ptr->rear + 1) % BUFFER_SIZE;
        ptr->buffer[ptr->rear] = data;
        ptr->size++;
        // ptr->rear=rear;
    }
}

item remove_item(Queue *ptr)
{
    item data;
    // int rear=ptr->rear;
    // int front=ptr->front;
    if (ptr->rear == ptr->front)
    {
        printf("Buffer underflow\n");
        return -1;
    }
    else
    {
        ptr->front = (ptr->front + 1) % BUFFER_SIZE;
        data = ptr->buffer[ptr->front];
        ptr->size--;
        // ptr->front=ptr->front-1;
    }
    return data;
}