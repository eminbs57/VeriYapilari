#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

// sirali ekleme fonksiyonu
void addOrdered(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    // liste bossa veya ilk elemandan kucukse basa ekle
    if (*head == NULL || (*head)->value >= value) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    // uygun yeri bulana kadar ilerle
    Node* iter = *head;
    while (iter->next != NULL && iter->next->value < value) {
        iter = iter->next;
    }
    
    newNode->next = iter->next;
    iter->next = newNode;
}

// ilk bulunan degeri sil
void removeNode(Node** head, int value) {
    if (*head == NULL) return;

    // silinecek olan bastaysa
    if ((*head)->value == value) {
        Node* tmp = *head;
        *head = (*head)->next;
        free(tmp);
        return;
    }

    Node* iter = *head;
    while (iter->next != NULL && iter->next->value != value) {
        iter = iter->next;
    }

    if (iter->next != NULL) {
        Node* tmp = iter->next;
        iter->next = iter->next->next;
        free(tmp);
    }
}

// listedeki eleman sayisi
int count(Node* head) {
    int c = 0;
    while (head != NULL) {
        c++;
        head = head->next;
    }
    return c;
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
    
    int sayilar[] = {23, 11, 5, 9, 6, 4, 12, 24};
    int boyut = sizeof(sayilar) / sizeof(sayilar[0]);
    
    for (int i = 0; i < boyut; i++) {
        addOrdered(&head, sayilar[i]);
    }
    
    printf("Liste: ");
    printList(head);
    
    printf("Dugum sayisi: %d\n", count(head));
    
    removeNode(&head, 9);
    printf("9 silindikten sonra: ");
    printList(head);
    
    clear(&head);
    
    return 0;
}
