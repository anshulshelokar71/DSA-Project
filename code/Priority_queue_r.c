# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "Priority_queue_r.h"

void Init_Heap_r(Heap_r *h, int x) {
    
    h->A = (int*)malloc(sizeof(int) * x);
    h->rear = -1;
    h->size = x;
    return;
}


bool Heap_r_isEmpty(Heap_r *h) {
    
    if(h->rear == -1)
        return true;

    return false;
}


bool Heap_r_isFull(Heap_r *h) {

    if(h->rear == h->size-1)
        return true;

    return false;
}


void Heap_r_Insert(Heap_r *h, int value) {

    if(Heap_r_isFull(h)) {
        printf("Heap_r is Full !\n");
        return;
    }

    h->rear++;
    int i = h->rear;

    while(i > 0 && value < h->A[(i-1)/2]) {
        h->A[i] = h->A[(i-1)/2];
        i = (i-1)/2;
    }

    h->A[i] = value;

    return;
}


void Heap_rify(Heap_r *h, int index) {
    int largest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;

    if(left <= h->rear && h->A[left] < h->A[largest])
        largest = left;
    if(right <= h->rear && h->A[right] < h->A[largest])
        largest = right;
    
    if(largest != index) {
        int temp = h->A[index];
        h->A[index] = h->A[largest];
        h->A[largest] = temp;
        Heap_rify(h, largest);
    }
}


int Heap_r_remove(Heap_r *h) {

    if(Heap_r_isEmpty(h)) {
        printf("Heap_r is Empty !\n");
        return 0;
    }

    int temp = h->A[0];
    h->A[0] = h->A[h->rear];
    h->rear--;
    Heap_rify(h, 0);

    return temp;
}


int Heap_r_top(Heap_r *h) {
    
    if(Heap_r_isEmpty(h)) {
        printf("Heap_r is Empty !\n");
        return -1;
    }

    return h->A[0];
}


// int main() {

//     Heap_r h;
//     Init_Heap_r(&h, 20);

//     Heap_r_Insert(&h, 10);
//     Heap_r_Insert(&h, 20);
//     printf("%d",Heap_r_top(&h));
//     Heap_r_remove(&h);
//     printf("%d",Heap_r_top(&h));

//     return 0;
// }
