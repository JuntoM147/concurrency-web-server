#ifndef QUEUE
#define QUEUE

#include <pthread.h>
#include <sys/_pthread/_pthread_cond_t.h>
#include <sys/_pthread/_pthread_mutex_t.h>

struct Node {
        int socket;
        struct Node *next;
};

typedef struct queue{
        int size;
        struct Node *head;
        struct Node *tail;
        pthread_mutex_t lock;
        pthread_cond_t not_empty;
} queue;

queue *queue_init();
void enqueue(queue *q, int socket);
int dequeue(queue *q);
int size(const queue *q);
void free_queue(queue *q);
void print_queue(const queue *q);

#endif
