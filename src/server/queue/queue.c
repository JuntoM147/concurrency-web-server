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
        struct Node* element = malloc(sizeof(struct Node));
        element->next = NULL;
        element->socket = socket;

        if (q->size == 0) {
                q->head = element;
                q->tail = element;
                q->size++;
                return;
        }

        struct Node* prev_tail = q->tail;
        q->tail = element;
        prev_tail->next = element;
        q->size++;
}

int dequeue(queue *q) {
        assert(q->size > 0);

        struct Node *old_head = q->head;
        int socket = old_head->socket;

        q->head = old_head->next;
        free(old_head);

        q->size--;

        if (q->size == 0) {
                q->tail = NULL;
        }

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

int size(queue *q) {
        return q->size;
}

void free_queue(queue *q) {
        struct Node *tmp, *curr = q->head;

        while (curr != NULL) {
                tmp = curr->next;
                free(curr);
                curr = tmp;
        }
        free(q);
}
