#include "queue.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

queue *queue_init() {
        queue *q = malloc(sizeof(queue));

        q->size = 0;
        q->head = NULL;
        q->tail = NULL;
        pthread_mutex_init(&(q->lock), NULL);
        pthread_cond_init(&(q->not_empty), NULL);

        return q;
}

void enqueue(queue *q, int socket) {
        pthread_mutex_lock(&(q->lock));

        struct Node* element = malloc(sizeof(struct Node));
        element->next = NULL;
        element->socket = socket;

        if (q->size == 0) {
                q->head = element;
                q->tail = element;
        } else {
                struct Node* prev_tail = q->tail;
                q->tail = element;
                prev_tail->next = element;
        }

        q->size++;

        pthread_cond_signal(&(q->not_empty));

        pthread_mutex_unlock(&(q->lock));
}

int dequeue(queue *q) {
        pthread_mutex_lock(&(q->lock));

        while (q->size == 0) {
                pthread_cond_wait(&(q->not_empty), &(q->lock));
        }

        struct Node *old_head = q->head;
        int socket = old_head->socket;

        q->head = old_head->next;
        free(old_head);

        q->size--;

        if (q->size == 0) {
                q->tail = NULL;
        }

        pthread_mutex_unlock(&(q->lock));

        return socket;
}

void print_queue(const queue *q) {
        struct Node *curr = q->head;

        while (curr != NULL) {
                printf("%d -> ", curr->socket);
                curr = curr->next;
        }

        printf("NULL\n");
}

int size(const queue *q) {
        return q->size;
}

void free_queue(queue *q) {
        struct Node *tmp, *curr = q->head;

        while (curr != NULL) {
                tmp = curr->next;
                free(curr);
                curr = tmp;
        }

        pthread_mutex_destroy(&(q->lock));
        pthread_cond_destroy(&(q->not_empty));
        free(q);
}
