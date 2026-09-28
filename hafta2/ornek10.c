#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

int main()
{
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    struct Node *node2 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *node3 = (struct Node *)malloc(sizeof(struct Node));
    struct Node *node4 = (struct Node *)malloc(sizeof(struct Node));

    head->data = 10;
    head->next = node2;

    node2->data = 20;
    node2->next = node3;

    node3->data = 30;
    node3->next = node4;

    node4->data = 40;
    node4->next = NULL;

    int silinecek;
    printf("Silinecek degeri giriniz: ");
    scanf("%d", &silinecek);

    struct Node *current = head;
    struct Node *previous = NULL;

    if (current != NULL && current->data == silinecek)
    {
        head = current->next;
        free(current);
    }
    else
    {
        while (current != NULL && current->data != silinecek)
        {
            previous = current;
            current = current->next;
        }

        if (current != NULL)
        {
            previous->next = current->next;
            free(current);
        }
        else
        {
            printf("Deger listede bulunamadi.\n");
        }
    }

    current = head;
    while (current != NULL)
    {
        printf("[%d] -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    current = head;
    struct Node *temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}