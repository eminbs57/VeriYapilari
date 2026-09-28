#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

void insertBeginning(struct Node **head_ref, int new_data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void display(struct Node *node)
{
    while (node != NULL)
    {
        printf("[%d] -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

void search(struct Node *head, int x)
{
    struct Node *current = head;
    int bulundu = 0;

    while (current != NULL)
    {
        if (current->data == x)
        {
            bulundu = 1;
            break;
        }
        current = current->next;
    }

    if (bulundu)
    {
        printf("%d degeri listede bulundu.\n", x);
    }
    else
    {
        printf("%d degeri listede bulunamadi.\n", x);
    }
}

int main()
{
    struct Node *head = NULL;

    insertBeginning(&head, 30);
    insertBeginning(&head, 20);
    insertBeginning(&head, 10);

    printf("Liste: ");
    display(head);

    search(head, 20);
    search(head, 40);

    struct Node *current = head;
    struct Node *temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}