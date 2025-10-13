#include "queue.h"
#include <stdio.h>


int main() {
        queue *my_q; = queue_init();

        for (int i = 0; i < 10; i++) {
                enqueue(my_q, i);
        }

        print_queue(my_q);

        for (int i = 0; i < 10; i++) {
                printf("Deque: %d\n", dequeue(my_q));
        }

        print_queue(my_q);

        free_queue(my_q);

}
