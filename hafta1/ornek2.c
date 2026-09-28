#include <stdio.h>

int main()
{
    int sayi, tersSayi = 0, kalan, orijinalSayi;

    printf("Bir tam sayi giriniz: ");
    scanf("%d", &sayi);

    orijinalSayi = sayi;

    // sayiyi terse cevirme
    while (sayi != 0)
    {
        kalan = sayi % 10;                // sayinin son basamagi
        tersSayi = tersSayi * 10 + kalan; // Ters sayiya basamagi ekle
        sayi /= 10;                       // sayinin son basamagini at
    }

    // karsilastir
    if (orijinalSayi == tersSayi)
    {
        printf("%d bir Palindrom sayidir.\n", orijinalSayi);
    }
    else
    {
        printf("%d bir Palindrom sayi degildir.\n", orijinalSayi);
    }

    return 0;
}