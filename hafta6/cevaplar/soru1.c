#include <stdio.h>
#include <stdlib.h>

// dugum yapisi
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// yeni dugum olusturma fonksiyonu
struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// bst eleman ekleme fonksiyonu
struct Node *insert(struct Node *root, int value)
{
    // agac bossa veya bos yapraga ulasildiysa dugumu olustur
    if (root == NULL)
    {
        return createNode(value);
    }

    // deger kokten kucukse sola ekle
    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    // deger kokten buyukse saga ekle
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }
    // ayni deger varsa hicbir sey yapma (yeni dugum olusmaz)

    return root;
}

// kucukten buyuge yazdiran fonksiyon (inorder)
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);       // once sol alt agac
        printf("%d ", root->data); // koku yazdir
        inorder(root->right);      // sonra sag alt agac
    }
}

int main()
{
    struct Node *root = NULL;

    // soruda istenen degerleri sirasiyla agaca ekliyoruz
    root = insert(root, 40);
    root = insert(root, 20);
    root = insert(root, 60);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 50);
    root = insert(root, 70);

    // agacin elemanlarini kucukten buyuge yazdiriyoruz
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    return 0;
}