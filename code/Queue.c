#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Queue.h"

void Init_queue(queue *q, int len) {

    q->size = len;
    q->front = q->rear = -1;
    q->Q = (int *)malloc(sizeof(int) * len);
}

int queue_isFull(queue q) {

    if (q.rear == q.size - 1) {
        printf("Queue is Full");
        return 1;
    }
    else
        return 0;
}

int queue_isEmpty(queue q) {

    if (q.front == q.rear) {
        printf("Queue is Empty\n");
        return 1;
    }
    else
        return 0;
}

void queue_enqueue(queue *q, int x) {

    if (!queue_isFull(*q)) {
        q->rear++;
        q->Q[q->rear] = x;
        return;
    }
}

int queue_dequeue(queue *q) {

    int x = INT_MIN;
    if (!queue_isEmpty(*q)) {
        q->front++;
        x = q->Q[q->front];
    }
    return x;
}



// int main() {

//     queue q;
//     Init_queue(&q, 5);



    

//     return 0;
// }
