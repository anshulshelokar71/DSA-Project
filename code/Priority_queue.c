# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "Priority_queue.h"

void Init_Heap(Heap *h, int x) {
    
    h->A = (int*)malloc(sizeof(int) * x);
    h->rear = -1;
    h->size = x;
    return;
}


bool Heap_isEmpty(Heap *h) {
    
    if(h->rear == -1)
        return true;

    return false;
}


bool Heap_isFull(Heap *h) {

    if(h->rear == h->size-1)
        return true;

    return false;
}


void Heap_Insert(Heap *h, int value) {

    if(Heap_isFull(h)) {
        printf("Heap is Full !\n");
        return;
    }

    h->rear++;
    int i = h->rear;

    while(i > 0 && value > h->A[(i-1)/2]) {
        h->A[i] = h->A[(i-1)/2];
        i = (i-1)/2;
    }

    h->A[i] = value;

    return;
}


void Heapify(Heap *h, int index) {
    int largest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;

    if(left <= h->rear && h->A[left] > h->A[largest])
        largest = left;
    if(right <= h->rear && h->A[right] > h->A[largest])
        largest = right;
    
    if(largest != index) {
        int temp = h->A[index];
        h->A[index] = h->A[largest];
        h->A[largest] = temp;
        Heapify(h, largest);
    }
}


int Heap_remove(Heap *h) {

    if(Heap_isEmpty(h)) {
        printf("Heap is Empty !\n");
        return 0;
    }

    int temp = h->A[0];
    h->A[0] = h->A[h->rear];
    h->rear--;
    Heapify(h, 0);

    return temp;
}


int Heap_top(Heap *h) {
    
    if(Heap_isEmpty(h)) {
        printf("Heap is Empty !\n");
        return -1;
    }

    return h->A[0];
}


// int main() {

//     Heap h;
//     Init_Heap(&h, 20);

//     Heap_Insert(&h, 10);
//     Heap_Insert(&h, 20);
//     printf("%d",Heap_top(&h));
//     Heap_remove(&h);
//     printf("%d",Heap_top(&h));

//     return 0;
// }