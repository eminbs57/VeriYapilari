#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

// pozisyona gore araya veya sona ekleme
void insertAt(Node** head, int value, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    // basa ekleme (pozisyon 0 veya negatifse ya da liste bossa)
    if (*head == NULL || position <= 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* iter = *head;
    int index = 0;
    
    // istenen pozisyona veya listenin sonuna kadar git
    while (iter->next != NULL && index < position - 1) {
        iter = iter->next;
        index++;
    }

    // araya veya en sona ekle
    newNode->next = iter->next;
    iter->next = newNode;
}

// pozisyona gore silme
void deleteAt(Node** head, int position) {
    if (*head == NULL || position < 0) return; // gecersiz durumlar

    // bastaki elemani silme
    if (position == 0) {
        Node* tmp = *head;
        *head = (*head)->next;
        free(tmp);
        return;
    }

    Node* iter = *head;
    int index = 0;

    // silinecek elemandan bir oncekine kadar git
    while (iter->next != NULL && index < position - 1) {
        iter = iter->next;
        index++;
    }

    // eger bulundugumuz dugumden sonra silinecek bir sey varsa
    if (iter->next != NULL) {
        Node* tmp = iter->next;
        iter->next = iter->next->next;
        free(tmp);
    }
}

// listeyi ekrana bas
void printList(Node* head) {
    while (head != NULL) {
        printf("%d", head->value);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("\n");
}

// bellegi bosalt
void clear(Node** head) {
    Node* p = *head;
    while (p != NULL) {
        Node* n = p->next;
        free(p);
        p = n;
    }
    *head = NULL;
}

int main() {
    Node* head = NULL;

    // test eklemeleri
    insertAt(&head, 10, 0); // 10
    insertAt(&head, 20, 1); // 10 -> 20
    insertAt(&head, 30, 5); // 10 -> 20 -> 30 (5>eleman sayisi, sona ekler)
    insertAt(&head, 5, -2); // 5 -> 10 -> 20 -> 30 (-2, basa ekler)
    insertAt(&head, 15, 2); // 5 -> 10 -> 15 -> 20 -> 30 (2. indise ekler)

    printf("Liste: ");
    printList(head);

    deleteAt(&head, 0);
    printf("0. indis silindikten sonra: ");
    printList(head);

    deleteAt(&head, 2);
    printf("2. indis silindikten sonra: ");
    printList(head);

    deleteAt(&head, 10);
    printf("Gecersiz indis denemesinden sonra: ");
    printList(head);

    clear(&head);
    return 0;
}
