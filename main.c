#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedlist.h"

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

bool test(list *head, int* ans, int len) {
    list *curr = head;
    if (!curr) {
        printf("The linked list is empty!\n");
        return false;
    }
    
    qsort(ans, len, sizeof(int), cmpfunc);
    curr = sort(head);

    int i = 0;
    while (i < len) {
        if (curr->data != ans[i]) {
            return false;
        }
        curr = curr->next;
        i++;
    }
    print(curr, false);
    return true;

}
int main() {
    int correct = 0, i = 0;
    srand(time(NULL));
   // for ( i = 0; i < 100; i++) {
        int testcase[10] = {0};
        for (int j = 0; j < 10; j++)
            testcase[j] = rand() % 50;
        
        list *head = NULL;
        for (int j = 9; j >= 0; j--)
            push(&head, testcase[j]);
        printf("Testcase %d: ", i+1);
        print(head, false);
        printf(" --> ");
        if (test(head, testcase, 10))
       //     correct++;
        list_free(&head);
        printf("\n");
    //}
  //  printf("%d/100 passed.\n", correct);

    return 0;
}
