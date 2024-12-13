#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    void *value;
    struct ListNode *next;
}ListNode;

int add(void *value);
int delete(void *value);
ListNode* find(void *value);
//int update(Linklist *node, void *value);
int update(void *old_value, void *new_value);

int printlist(void);
