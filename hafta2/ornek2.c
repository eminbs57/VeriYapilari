#include <stdio.h>
#include <stdlib.h> // malloc için gerekli

struct Node
{
    int data;
    struct Node *next;
};

int main()
{

    struct Node *node1 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *node2 = (struct Node *)malloc(sizeof(struct Node));

    node1->data = 10;
    node2->data = 20;

    node1->next = node2;
    node2->next = NULL;

    printf("%d -> %d -> NULL\n", node1->data, node1->next->data);

    return 0;
}