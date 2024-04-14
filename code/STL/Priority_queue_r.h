
typedef struct Heap_r {
    int *A;
    int size;
    int rear;
} Heap_r;


void Init_Heap_r(Heap_r *, int);
bool Heap_r_isEmpty(Heap_r *h);
bool Heap_r_isFull(Heap_r *h);
void Heap_r_Insert(Heap_r *h, int value);
void Heap_rify(Heap_r *h, int index);
int Heap_r_remove(Heap_r *h);
int Heap_r_top(Heap_r *h);