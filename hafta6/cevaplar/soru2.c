#include <stdio.h>
#include <stdlib.h>

// dugum yapisi (main icinde Node* root seklinde kullanabilmek icin typedef eklendi)
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// yeni dugum olusturma
Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// bst eleman ekleme fonksiyonu
Node *insert(Node *root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }
    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }
    return root;
}

// arama fonksiyonu: bulunduysa 1, bulunamadiysa 0 dondurur
int search(Node *root, int key)
{
    // agac bossa veya dugum bulunamadiysa
    if (root == NULL)
    {
        return 0;
    }

    // deger bulunduysa
    if (root->data == key)
    {
        return 1;
    }

    // aranan deger kokten kucukse sol alt agacta ara
    if (key < root->data)
    {
        return search(root->left, key);
    }
    // aranan deger kokten buyukse sag alt agacta ara
    else
    {
        return search(root->right, key);
    }
}

// agactaki en kucuk degeri donduren fonksiyon
// bst ozelligi geregi en kucuk deger her zaman en soldaki dugumdedir
int findMin(Node *root)
{
    Node *current = root;

    // en soldaki dugume kadar gidiyoruz
    while (current->left != NULL)
    {
        current = current->left;
    }

    return current->data;
}

// soruda verilen main fonksiyonu
int main()
{
    Node *root = NULL;
    int numbers[] = {40, 20, 60, 10, 30, 50, 70};

    for (int i = 0; i < 7; i++)
        root = insert(root, numbers[i]);

    if (search(root, 30))
        printf("30 agacta bulundu.\n");
    else
        printf("30 agacta bulunamadi.\n");

    if (search(root, 90))
        printf("90 agacta bulundu.\n");
    else
        printf("90 agacta bulunamadi.\n");

    if (root != NULL)
        printf("En kucuk eleman: %d\n", findMin(root));

    return 0;
}