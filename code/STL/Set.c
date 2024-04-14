# include <stdio.h>
# include <stdlib.h>
# include "Set.h"

#define RED 0
#define BLACK 1



set_Node *set_createset_Node(int data) {

    set_Node *newset_Node = (set_Node *)malloc(sizeof(set_Node));
    
    if (newset_Node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    newset_Node->data = data;
    newset_Node->color = RED;   
    newset_Node->parent = NULL;
    newset_Node->left = NULL;
    newset_Node->right = NULL;
    return newset_Node;
}


set_Node *minimum(set_Node *set_Node) {

    while (set_Node->left != NULL)
        set_Node = set_Node->left;

    return set_Node;
}


void transplant(set_Node **root, set_Node *u, set_Node *v) {

    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    
    if (v != NULL)
        v->parent = u->parent;
}


void leftRotate(set_Node **root, set_Node *x) {

    set_Node *y = x->right;
    x->right = y->left;
    
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}


void rightRotate(set_Node **root, set_Node *y) {
    
    set_Node *x = y->left;
    y->left = x->right;
    
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}


void deleteFixup(set_Node **root, set_Node *x) {

    while (x != *root && x->color == BLACK) {
        
        if (x == x->parent->left) {
            
            set_Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }

        } else {

            set_Node *w = x->parent->left;
            
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {

                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }

        }
    }
    x->color = BLACK;
}


void set_delete(set_Node **root, int data) {

    set_Node *z = *root;
    while (z != NULL) {
        if (z->data == data)
            break;
        if (z->data < data)
            z = z->right;
        else
            z = z->left;
    }
    if (z == NULL) {
        return;
    }

    set_Node *y = z;
    set_Node *x;
    int y_original_color = y->color;

    if (z->left == NULL) {

        x = z->right;
        transplant(root, z, z->right);
    
    } else if (z->right == NULL) {
    
        x = z->left;
        transplant(root, z, z->left);
    
    } else {

        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK)
        deleteFixup(root, x);
    free(z);
}


void set_insertFixup(set_Node **root, set_Node *z) {

    while (z != *root && z->parent->color == RED) {
        
        if (z->parent == z->parent->parent->left) {
            
            set_Node *y = z->parent->parent->right;
            
            if (y != NULL && y->color == RED) {
                
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            
            } else {
                
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {

            set_Node *y = z->parent->parent->left;
            
            if (y != NULL && y->color == RED) {

                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            
            } else {

                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }

    (*root)->color = BLACK;
}


void set_insert(set_Node **root, int data) {

    set_Node *z = set_createset_Node(data);
    set_Node *y = NULL;
    set_Node *x = *root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    set_insertFixup(root, z);
}


void set_display(set_Node *root) {

    if (root != NULL) {
        set_display(root->left);
        printf("%d ", root->data);
        set_display(root->right);
    }
}


set_Node *set_search(set_Node *root, int data) {

    while (root != NULL) {
        if (data == root->data)
            return root;
        else if (data < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}


int set_count(set_Node *root, int data) {

    while (root != NULL) {
        if (data == root->data)
            return 1;
        else if (data < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return 0;
}


// int main() {

//     set_Node *root = NULL;

//     set_insert(&root, 10);
//     set_insert(&root, 20);
//     set_insert(&root, 30);
//     set_insert(&root, 15);
//     set_insert(&root, 25);

//     printf("Inorder Traversal: ");
//     set_display(root);
//     printf("\n");

//     set_delete(&root, 10); // Delete set_Node with value 20

//     printf("Inorder Traversal after deletion: ");
//     set_display(root);
//     printf("\n");
//     set_search(root, 10) ? printf("Is present ") : printf("Nor Present");

//     return 0;
// }
