typedef struct node {
	int data;
	struct node *next;
}node;

typedef node* list;

typedef struct stack {
	list l;
	node *top;
}stack;

void init_stack(stack *s);
void init_list(list *l);
int stack_isempty(stack s);
void stack_push(stack *s,int d);
int stack_pop(stack *s);
int stack_peek(stack s);
void stack_insert(list *l,int d);
void stack_delete1(list *l);
int stack_isemptyl(list l);
void stack_display(stack s);