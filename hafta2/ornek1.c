#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;          // Veriyi tutacak kısım
    struct Node *next; // Bir sonraki dugumu isart edecek pointer (null)
};

int main()
{
    // Yeni bir node icin bellekte (heap) yer ayırıyoruz
    struct Node *dugum = (struct Node *)malloc(sizeof(struct Node));

    //  Istenen degerleri atıyoruz
    dugum->data = 10;   // icersine 10 degerini sakliyorsz
    dugum->next = NULL; // Tek node olduğu için sonrasını null yapıyoruz

    //  degeri ekrana bastir
    printf("Node icerisindeki deger: %d\n", dugum->data);

    return 0;
}