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
    if (!start || !start->next)
        return start;
    list *left = start;
    list *right = left->next;
    left->next = NULL; // partition input list into left and right sublist

    left = sort(left); // list of single element is already sorted
    right = sort(right); // sorted right sublist

    // insertion until the two sublists both been traversed
    // merge is always infront of the insertion position
    for (list *merge = NULL; left || right;) {
        // right list hasn't reach the end or
        // left node has found its position for inserting
        if (right == NULL || (left && left->data < right->data)) {
            if (!merge) {
                // start points to the node with min value
                // merge starts from min value
                start = merge = left; // LL1
            }
            else {
                // insert left node between merge and right point to
                merge->next = left; // LL2
                merge = merge->next; 
            }
            left = left->next; // LL3
        }
        else {
            if (!merge) {
                start = merge = right; // LL4
            } else {
                // shift until right == NULL or
                // inset merge(=left) in front of right when min is in left sublist
                // (LL1->LL5-> shift until right == NULL)
                merge->next = right; // LL5
                merge = merge->next;
            }
            right = right->next; // LL6
        }
    }
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