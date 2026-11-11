#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(Node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

Node *createNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int balanceFactor(Node *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// Sağa Rotasyon (LL durumu için)
Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

// Sola Rotasyon (RR durumu için)
Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// DÖRT ROTASYONU DESTEKLEYEN GENEL AVL EKLEME FONKSİYONU
Node *insertAVL(Node *node, int key)
{
    // 1. Standart BST Eklemesi
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node;

    // 2. Yükseklik Güncelleme
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Denge Faktörü Kontrolü
    int balance = balanceFactor(node);

    // Durum 1: LL (Left-Left) -> Sağa Tek Rotasyon
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Durum 2: RR (Right-Right) -> Sola Tek Rotasyon
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Durum 3: LR (Left-Right) -> Sol-Sağ Çift Rotasyon
    if (balance > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Durum 4: RL (Right-Left) -> Sağ-Sol Çift Rotasyon
    if (balance < -1 && key < node->right->key)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Preorder Dolaşım
void preorder(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// Dört testi bağımsız olarak koşturan yardımcı fonksiyon
void runTest(const char *testAdi, int dizi[], int n)
{
    Node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        root = insertAVL(root, dizi[i]);
    }
    printf("%s -> Kok: %d | Preorder: ", testAdi, root->key);
    preorder(root);
    printf("\n");
}

int main()
{
    int testA[] = {30, 20, 10}; // LL
    int testB[] = {10, 20, 30}; // RR
    int testC[] = {30, 10, 20}; // LR
    int testD[] = {10, 30, 20}; // RL

    printf("=== AVL DÖRT ROTASYON TESTLERI ===\n");
    runTest("Test A (LL)", testA, 3);
    runTest("Test B (RR)", testB, 3);
    runTest("Test C (LR)", testC, 3);
    runTest("Test D (RL)", testD, 3);

    return 0;
}