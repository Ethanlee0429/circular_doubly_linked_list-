#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedlist.h"

void push(list **head_ref, int data) {
    list *new_head = malloc(sizeof(list));
    new_head->data = data;
    if (!*head_ref) {
      *head_ref = new_head;
      new_head->next = new_head;
      new_head->prev = new_head;
    }
    list *lastnode = (*head_ref)->prev;
    new_head->next = *head_ref;
    new_head->prev = lastnode;
    (*head_ref)->prev = new_head;
    lastnode->next = new_head;
    *head_ref = new_head;
    return;
}

void print(list *head, bool newline) {
    list *curr = head;
    if (!curr)
        printf("The linked list is empty!\n");

    while (curr->next != head) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("%d ", curr->data);
    if (newline)
      printf("\n");
}

list *sort(list *start) {
    if (!start || (start->next == start))
        return start;
    list *left = start;
    list *right = left->next;

    left->prev->next  = right;
    right->prev = left->prev;

    left->next = left;
    left->prev = left;

    left = sort(left); 
    right = sort(right);
    printf("=== left->data = %d first right = %d ===\n", left->data, right->data);
    for (list *merge = NULL; left || right != start;) {
        if (right == start || (left && left->data < right->data)) {
            if (!merge) {
                printf("start = left = %d\n",left->data);
                start = merge = left;
            }
            else {
                printf("1 .merge data = %d left = %d\n",merge->data,left->data);
                left->prev = merge;
                left->next = merge->next;
                merge->next->prev = left;
                merge->next = left;
                merge = merge->next; 
            }
            left = NULL;
        }
        else {
            if (!merge) {
                printf("start = right = %d\n",right->data);
                start = merge = right;
            } else {
                if (merge == merge->next){
                    printf("2-1 .merge data = %d next = %d right = %d\n",merge->data,merge->next->data,right->data);
                    merge->next = right;
                    merge->prev = right->prev;//
                    right->prev->next = merge;//
                    right->prev = merge;
                } else 
                {
                     printf("2-2 .merge data = %d next = %d right = %d\n",merge->data,merge->next->data,right->data);
                }
                merge = merge->next;
            }
            right = right->next;
        }
    }
    printf("\n");
    return start;
}
void list_free(list **Input) {
    list *head = *Input;
    list *tmp;
     // free(start);
    *Input = (*Input)->next;
    while (head != *Input) {
        tmp = (*Input)->next;
        free(*Input);
        *Input = tmp;
    }
    free(*Input);
}