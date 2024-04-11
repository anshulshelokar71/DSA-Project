#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct queue{
    int rear;
    int front;
    int size;
    int *Q;

}queue;


void Init_queue(queue *q,int len);
int queue_isFull(queue q);
int queue_isEmpty(queue q);
void queue_enqueue(queue *q,int x);
int queue_dequeue(queue *q);

#endif // QUEUE_H_INCLUDED
