struct set_Node {

    int data;
    int color;
    struct set_Node *parent;
    struct set_Node *left;
    struct set_Node *right;
};

typedef struct set_Node set_Node;

set_Node *set_createset_Node(int data);
set_Node *minimum(set_Node *set_Node);
void transplant(set_Node **root, set_Node *u, set_Node *v);
void leftRotate(set_Node **root, set_Node *x);
void rightRotate(set_Node **root, set_Node *y);
void deleteFixup(set_Node **root, set_Node *x);
void set_delete(set_Node **root, int data);
void set_insertFixup(set_Node **root, set_Node *z);
void set_insert(set_Node **root, int data);
void set_display(set_Node *root);
set_Node *set_search(set_Node *root, int data);
int set_count(set_Node *root, int data);