#ifndef QUEUE
#define QUEUE

#include <pthread.h>

struct Node {
        int socket;
        struct Node *next;
};

typedef struct queue{
        int size;
        struct Node *head;
        struct Node *tail;
} queue;

queue *queue_init();
void enqueue(queue *q, int socket);
int dequeue(queue *q);
int size(queue *q);
void free_queue(queue *q);
void print_queue(const queue *q);

#endif
