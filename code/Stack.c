# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "Stack.h"

void init_list(list *l) {
    *l = NULL;
    return;
}

void stack_insert(list *l, int d) {
    node *p, *nn;
    nn = (node *)malloc(sizeof(node));
    if (nn)
    {
        nn->data = d;
        nn->next = NULL;
    }
    else
        return;
    nn->next = *l;
    *l = nn;
    return;
}

void stack_delete1(list *l) {
    node *p = *l;

    // if there are no nodes in Linked List can't delete
    if (!p)
        return;

    *l = p->next;
    free(p);

    return;
}

int stack_isemptyl(list l)
{
    if (!(l))
        return 1;
    else
        return 0;
}

void init_stack(stack *s) {
    init_list(&(s->l));
    s->top = NULL;
    return;
}

int stack_isempty(stack s) {
    if (s.top == NULL)
        return 1;
    else
        return 0;
}

void stack_push(stack *s, int d) {
    stack_insert(&(s->l), d);
    node *p = s->l;
    s->top = s->l;
    return;
}

int stack_peek(stack s) {
    if (stack_isempty(s))
        return INT_MAX;
    else
        return ((s.top)->data);
}

int stack_pop(stack *s) {
    if (stack_isempty(*s))
        return INT_MAX;
    int j = stack_peek(*s);
    stack_delete1(&(s->l));
    s->top = s->l;
    return j;
}

void stack_display(stack s) {
    if (stack_isempty(s))
    {
        printf("Stack is empty");
        return;
    }
    printf("[ ");
    node *p = s.top;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("]\n");
    return;
}