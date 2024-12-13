#include "Linklist.h"


ListNode *head = NULL;

ListNode* create_node() {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));

     if (!node) {
        printf("内存分配失败\n");
        exit(1);
    }
    return node;
}

int add(void *value) {
    if(head == NULL) {
        //head = (ListNode*)malloc(sizeof(ListNode));
        //可能需要判断malloc是否成功，return -1
        head = create_node();

        head->value = value;
        head->next = NULL;
    } else {
        ListNode *tmp = head;

        while(tmp->next != NULL) {
            tmp = tmp->next;
        }

        ListNode *new_node = create_node();
        new_node->value = value;
        new_node->next = NULL;

        tmp->next = new_node; //连接
    }
    return 0;
}



int delete(void *value) {

    ListNode *temp = head;
    ListNode *prev = NULL;

    if (temp != NULL && temp->value == value) {
        head = temp->next; // 修改头指针
        free(temp);         // 释放旧头结点
        return 1;
    }

    // 查找要删除的节点
    while (temp != NULL && temp->value != value) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL) {
        prev->next = temp->next;
        free(temp);

        return 0;
    }

    return 0;
}

ListNode* find(void *value) {

    ListNode *temp = head;

    while(temp != NULL && temp->value != value) {
        temp = temp->next;
    }

    if (temp != NULL) {
        return temp;
    }

    return NULL;
}


int update(void *old_value, void *new_value) {

    ListNode *temp = head;

    while(temp != NULL && temp->value != old_value) {
        temp = temp->next;
    }

    if (temp != NULL) {
        old_value = new_value;
        return 1;
    }

    return 0;
}

int printlist(void)
{
    ListNode *temp = head;

    while(temp != NULL) {
        printf("%d\n", *(int*)(temp->value));
        temp = temp->next;
    }
    return 0;
}
