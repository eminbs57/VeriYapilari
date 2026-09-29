#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

// ortadaki dugumu bulan fonksiyon (iki gosterici teknigi)
Node* findMiddle(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* slow = head;
    Node* fast = head;

    // fast 2 adim, slow 1 adim ilerler
    // fast sona ulastiginda slow ortada kalir
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          // 1 adim
        fast = fast->next->next;    // 2 adim
    }

    return slow;
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

// test edebilmek icin listeye eleman ekleme fonksiyonu
void append(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* iter = *head;
    while (iter->next != NULL) {
        iter = iter->next;
    }
    iter->next = newNode;
}

int main() {
    Node* head = NULL;

    // tek sayida eleman ekleyelim (5 eleman)
    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    append(&head, 40);
    append(&head, 50);

    printf("Liste (Tek sayida eleman): ");
    printList(head);

    Node* mid = findMiddle(head);
    if (mid != NULL) {
        // 5 elemanin ortasi 30 olmali
        printf("Ortadaki dugum: %d\n\n", mid->value); 
    }

    // cift sayida eleman yapmak icin 1 tane daha ekleyelim (6 eleman)
    append(&head, 60);
    printf("Liste (Cift sayida eleman): ");
    printList(head);

    mid = findMiddle(head);
    if (mid != NULL) {
        // 6 elemanin ortasindaki ikiliden (30 ve 40) ikincisi yani 40 olmali
        printf("Ortadaki dugum: %d\n", mid->value); 
    }

    clear(&head);
    return 0;
}
