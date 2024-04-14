
typedef struct Heap {
    int *A;
    int size;
    int rear;
} Heap;


void Init_Heap(Heap *, int);
bool Heap_isEmpty(Heap *h);
bool Heap_isFull(Heap *h);
void Heap_Insert(Heap *h, int value);
void Heapify(Heap *h, int index);
int Heap_remove(Heap *h);
int Heap_top(Heap *h);