#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

typedef struct __list {
    int data;
    struct __list *next;
    struct __list *prev;
} list;

typedef struct list List;
void push(list **head_ref, int data);
void print(list *head, bool newline);
list *sort(list *start) ;

#endif
