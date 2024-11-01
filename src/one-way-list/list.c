#include <stdio.h>
#include <stdlib.h>

struct list_node {
    int data;
    struct list_node *next;
};

int is_list_empty(struct list_node *head)
{
    return (head->next == NULL);
//    return head == NULL;  不带头结点
}

void list_print(struct list_node *head)
{
    struct list_node *p;
    p = head->next;
    for (p; p != NULL; p = p->next) {
        printf("list data = %d\n", p->data);
    }
}

void list_add_head(struct list_node *head, struct list_node *node)
{
    node->next = head->next;
    head->next = node;
}

void list_add_tail(struct list_node *head, struct list_node *node)
{
    struct list_node *p;
    for (p = head->next; p->next != NULL; p = p->next);
    p->next = node;    
}

int list_delete(struct list_node *head, struct list_node *node)
{
    struct list_node *p;

    if(is_list_empty(head)) {
        return -1;
    }

    if(node == head->next) {
        head->next = node->next;
    } else {
        for (p = head->next; p->next != node; p = p->next);
        p->next = node->next;
    }

    free(node);
}

void list_free(struct list_node *head)
{
    struct list_node *p, *q;

    q = head->next;
    p = q->next;

    while (q != NULL) {
        free(q);
        q = p;
        if(p != NULL) {
            p = p->next;
        }
        printf("p: %p  q: %p\n", p, q);
    }
}

struct list_node *list_foreach(struct list_node *haed, int val)
{
    struct list_node *p;

    p = haed->next;
    for (p; p->data != val; p = p->next);
    return p;
}

int main()
{
    struct list_node *p;
    struct list_node listhead, *head;

    head = &listhead;
    p = (struct list_node*)malloc(sizeof(struct list_node*));
    p->data = 0;
    p->next = NULL;
    head->next = p;

//  头插
    for (size_t i = 1; i <= 2; i++) {
        p = (struct list_node*)malloc(sizeof(struct list_node*));
        p->data = i;
        p->next = NULL;
        list_add_head(head, p);
    }

//  尾插
    for (size_t i = 2; i >= 1; i--) {
        p = (struct list_node*)malloc(sizeof(struct list_node*));
        p->data = i;
        p->next = NULL;
        list_add_tail(head, p);
    }

    // list_print(head);

    list_delete(head, head->next);

    list_print(head);

//  查找
    p = list_foreach(head, 2);
    printf("data = %d\n", p->data);

    list_free(head);

    return 0;
}