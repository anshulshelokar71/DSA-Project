# include "Queue.h"
# include <stdio.h>


int main() {

    queue q;
    Init_queue(&q, 100);

    queue_enqueue(&q, 12);
    queue_enqueue(&q, 23);

    printf("%d ", q);

    return 0;
}