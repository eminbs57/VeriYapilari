#include <stdio.h>
#include <stdlib.h>

// agac dugumu icin struct tanimi
struct Dugum {
    int veri;
    struct Dugum* sol;
    struct Dugum* sag;
};

// yeni dugum olusturan yardimci fonksiyon
struct Dugum* dugumOlustur(int sayi) {
    struct Dugum* yeni = (struct Dugum*)malloc(sizeof(struct Dugum));
    yeni->veri = sayi;
    yeni->sol = NULL;
    yeni->sag = NULL;
    return yeni;
}

// bst kuralina gore agaca eleman ekleme
struct Dugum* ekle(struct Dugum* kok, int sayi) {
    if (kok == NULL) {
        return dugumOlustur(sayi);
    }

    if (sayi < kok->veri) {
        kok->sol = ekle(kok->sol, sayi);
    } else if (sayi > kok->veri) {
        kok->sag = ekle(kok->sag, sayi);
    }

    return kok;
}

// agacin yuksekligini bulan fonksiyon (en kotu durum adim sayisi icin)
int yukseklikBul(struct Dugum* kok) {
    if (kok == NULL) {
        return 0;
    }

    int solYukseklik = yukseklikBul(kok->sol);
    int sagYukseklik = yukseklikBul(kok->sag);

    if (solYukseklik > sagYukseklik) {
        return solYukseklik + 1;
    } else {
        return sagYukseklik + 1;
    }
}

// rekursif hazine arama fonksiyonu
// her adimda hangi dugumde oldugunu ekrana basiyor
int hazineAra(struct Dugum* kok, int aranan) {
    // eger agac bos ise veya dugum bulunamadiysa
    if (kok == NULL) {
        return 0; // bulunamadi
    }

    // bonus: her adimda ziyaret edilen dugumu yazdiriyoruz
    printf("-> Ziyaret edilen dugum: %d\n", kok->veri);

    // hazineyi bulduysak 1 dondur
    if (kok->veri == aranan) {
        return 1;
    }

    // aranan deger kucukse sola, buyukse saga git
    if (aranan < kok->veri) {
        return hazineAra(kok->sol, aranan);
    } else {
        return hazineAra(kok->sag, aranan);
    }
}

int main() {
    struct Dugum* kok = NULL;

    // agaca ornek hazine degerleri ekliyoruz
    kok = ekle(kok, 50);
    ekle(kok, 30);
    ekle(kok, 70);
    ekle(kok, 20);
    ekle(kok, 40);
    ekle(kok, 60);
    ekle(kok, 80);

    printf("=== HAZINE AGACI OYUNUNA HOS GELDINIZ ===\n\n");

    // bonus: agac yuksekligini hesaplayip en kotu adim sayisini yazdiralim
    int enKotuDurum = yukseklikBul(kok);
    printf("Bilgi: Hazineyi bulmak icin en kotu durumda %d adim gerekir (Agac Yuksekligi).\n\n", enKotuDurum);

    // kullanicidan sayi aliyoruz
    int tahmin;
    printf("Hazine aramak icin bir sayi kazin (girin): ");
    scanf("%d", &tahmin);

    printf("\nKazma islemi basladi (Arama adimlari):\n");
    int bulunduMu = hazineAra(kok, tahmin);

    // sonuca gore ekrana yazdir
    if (bulunduMu == 1) {
        printf("\nHazine bulundu!\n");
    } else {
        printf("\nBosuna kazdin!\n");
    }

    return 0;
}