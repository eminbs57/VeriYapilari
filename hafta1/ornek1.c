#include <stdio.h>

int main()
{
    int n = 10;
    int dizi[n];
    int i;

    for (i = 0; i < n; i++)
    {
        printf("%d. elemani giriniz: ", i + 1);
        scanf("%d", &dizi[i]);
    }

    printf("\nGirilen elemanlar:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", dizi[i]);
    }

    printf("\n");
    return 0;
}