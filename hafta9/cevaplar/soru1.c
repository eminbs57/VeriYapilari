#include <stdio.h>
#include <stdlib.h>

// Düğüm Yapısı
typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// İki değerden büyük olanı döndürür
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Bir düğümün yüksekliğini döndürür (Boşsa 0)
int height(Node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

// Yeni bir düğüm oluşturan fonksiyon
Node *createNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Yeni yaprağın yüksekliği 1'dir
    return node;
}

// Denge Faktörü: Sol alt ağaç yüksekliği - Sağ alt ağaç yüksekliği
int balanceFactor(Node *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// Sola Rotasyon (RR Dengesizliği Çözümü)
Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Rotasyon işlemi
    y->left = x;
    x->right = T2;

    // Yükseklikleri güncelle
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    // Yeni kökü döndür
    return y;
}

// Standart BST Ekleme Fonksiyonu
Node *insertBST(Node *node, int key)
{
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);
    else
        return node;

    // Yükseklik güncelleme
    node->height = 1 + max(height(node->left), height(node->right));
    return node;
}

// Inorder Dolaşım (LNR)
void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Preorder Dolaşım (NLR)
void preorder(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

int main()
{
    Node *root = NULL;

    // 10 Ekle
    root = insertBST(root, 10);
    printf("10 eklendi. BF(kok) = %d\n", balanceFactor(root));

    // 20 Ekle
    root = insertBST(root, 20);
    printf("20 eklendi. BF(kok) = %d\n", balanceFactor(root));

    // 30 Ekle
    root = insertBST(root, 30);
    printf("30 eklendi. BF(kok) = %d\n", balanceFactor(root));

    // Dengesizlik kontrolü ve Sola Rotasyon
    if (balanceFactor(root) == -2)
    {
        printf("RR dengesizligi: Sol rotasyon!\n");
        root = rotateLeft(root);
    }

    // Beklenen çıktılar
    printf("Kok: %d\n", root->key);
    printf("Inorder: ");
    inorder(root);
    printf("\nPreorder: ");
    preorder(root);
    printf("\n");

    return 0;
}