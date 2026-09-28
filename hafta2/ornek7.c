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

    int aranan;
    int bulundu = 0;

    printf("Aranacak sayiyi giriniz: ");
    scanf("%d", &aranan);

    struct Node *current = head;

    while (current != NULL)
    {
        if (current->data == aranan)
        {
            bulundu = 1;
            break;
        }
        current = current->next;
    }

    if (bulundu == 1)
    {
        printf("Sayi listede bulundu.\n");
    }
    else
    {
        printf("Sayi listede bulunamadi.\n");
    }

    free(head);
    free(node2);
    free(node3);
    free(node4);

    return 0;
}