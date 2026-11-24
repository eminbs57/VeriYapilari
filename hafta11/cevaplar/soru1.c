#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 6 // Dugum sayisi (1'den 6'ya)

// Dugum derecelerini ve grafin genel derecesini hesaplayan fonksiyon
void dereceleriHesapla(int matris[N][N])
{
    int toplamDerece = 0;
    int maksDerece = 0;

    printf("--- 2. Dugum Dereceleri ve Grafin Genel Derecesi ---\n");
    for (int i = 0; i < N; i++)
    {
        int derece = 0;
        for (int j = 0; j < N; j++)
        {
            if (matris[i][j] == 1)
            {
                derece++;
            }
        }
        printf("Dugum %d Derecesi: %d\n", i + 1, derece);
        toplamDerece += derece;
        if (derece > maksDerece)
        {
            maksDerece = derece;
        }
    }

    printf("Grafin Toplam Derecesi (2 * |E|): %d\n", toplamDerece);
    printf("Grafin Maksimum Derecesi (Delta(G)): %d\n", maksDerece);
    printf("Grafin Ortalama Derecesi: %.2f\n\n", (float)toplamDerece / N);
}

// Bipartite (Iki Parcali Graf) kontrol fonksiyonu (BFS ve Renklendirme ile)
// Renkler: -1 = Boyanmamis, 0 = Mavi (Kume U), 1 = Kirmizi (Kume V)
bool bipartiteKontrol(int matris[N][N], int baslangicDugumu)
{
    int renk[N];
    int mesafe[N];

    for (int i = 0; i < N; i++)
    {
        renk[i] = -1;
        mesafe[i] = -1;
    }

    // Baslangic dugumu indeksi (1 numarali dugum icin indeks 0)
    int startIdx = baslangicDugumu - 1;

    // Basit FIFO Kuyruk yapisi
    int kuyruk[N];
    int front = 0, rear = 0;

    // Baslangic dugumunu 0 (Mavi) ile boya
    renk[startIdx] = 0;
    mesafe[startIdx] = 0;
    kuyruk[rear++] = startIdx;

    printf("--- 3. Bipartite Kontrolu (Baslangic Dugumu: %d) ---\n", baslangicDugumu);
    printf("Renklendirme ve Parite Durumlari:\n");

    bool ikiParcali = true;

    while (front < rear)
    {
        int u = kuyruk[front++];

        for (int v = 0; v < N; v++)
        {
            if (matris[u][v] == 1)
            {
                // Eger komsu dugum henuz boyanmamissa, ters renge boya
                if (renk[v] == -1)
                {
                    renk[v] = 1 - renk[u];
                    mesafe[v] = mesafe[u] + 1;
                    kuyruk[rear++] = v;
                }
                // Eger komsu dugum ayni renge sahipse, Bipartite degildir!
                else if (renk[v] == renk[u])
                {
                    ikiParcali = false;
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("Dugum %d -> Uzaklik: %d (%s), Renk: %s (%s)\n",
               i + 1,
               mesafe[i],
               (mesafe[i] % 2 == 0) ? "Cift" : "Tek",
               (renk[i] == 0) ? "0 (Mavi)" : "1 (Kirmizi)",
               (renk[i] == 0) ? "Kume U" : "Kume V");
    }

    if (ikiParcali)
    {
        printf("\nSONUC: Graf IKI PARCALIDIR (Bipartite).\n");
        printf("Kume U (Mavi / Cift Parite): { ");
        for (int i = 0; i < N; i++)
            if (renk[i] == 0)
                printf("%d ", i + 1);
        printf("}\n");

        printf("Kume V (Kirmizi / Tek Parite): { ");
        for (int i = 0; i < N; i++)
            if (renk[i] == 1)
                printf("%d ", i + 1);
        printf("}\n");
        printf("Guvenlik Politikasi: Kume icinde baglanti yoktur, ag guvenli!\n\n");
    }
    else
    {
        printf("\nSONUC: Graf IKI PARCALI DEGILDIR (Not Bipartite)!\n");
        printf("Nedeni: Ayni renge sahip komsu dugumler tespit edildi (Tek uzunluklu dongu olustu).\n");
        printf("Guvenlik Politikasi: Kendi kumesi icindeki cihazlar birbirine baglanarak kural ihlal edildi!\n\n");
    }

    return ikiParcali;
}

// Komsuluk matrisini ekrana yazdirma
void matrisYazdir(int matris[N][N])
{
    printf("    ");
    for (int j = 0; j < N; j++)
    {
        printf(" %d ", j + 1);
    }
    printf("\n   +------------------\n");
    for (int i = 0; i < N; i++)
    {
        printf(" %d |", i + 1);
        for (int j = 0; j < N; j++)
        {
            printf(" %d ", matris[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    printf("====================================================================\n");
    printf("     VERI YAPILARI - HAFTA 11: SORU 1 (BIPARTITE GRAF ANALIZI)      \n");
    printf("====================================================================\n\n");

    // 1. Veri Yapisi Olusturma: 6x6 Komsuluk Matrisi
    // Verilen kenarlar: E = {(1, 2), (1, 4), (2, 3), (3, 4), (3, 6), (4, 5), (5, 6)}
    int matris[N][N] = {0};

    int kenarlar[][2] = {
        {1, 2}, {1, 4}, {2, 3}, {3, 4}, {3, 6}, {4, 5}, {5, 6}
    };
    int kenarSayisi = sizeof(kenarlar) / sizeof(kenarlar[0]);

    for (int i = 0; i < kenarSayisi; i++)
    {
        int u = kenarlar[i][0] - 1;
        int v = kenarlar[i][1] - 1;
        matris[u][v] = 1;
        matris[v][u] = 1; // Yonsuz graf
    }

    printf("--- 1. Orijinal Komsuluk Matrisi (6x6) ---\n");
    matrisYazdir(matris);

    // 2. Derece Hesaplama
    dereceleriHesapla(matris);

    // 3. Bipartite Kontrolu (1 numarali dugum baslangic)
    bipartiteKontrol(matris, 1);

    // 4. Dinamik Test: Kenar listesine (2, 4) baglantisinin eklenmesi
    printf("====================================================================\n");
    printf("--- 4. Dinamik Test: (2, 4) Baglantisi Ekleniyor ---\n");
    printf("====================================================================\n");
    matris[1][3] = 1; // Dugum 2 ile 4 (indeks 1 ve 3)
    matris[3][1] = 1;

    printf("Guncel Komsuluk Matrisi:\n");
    matrisYazdir(matris);

    printf("Guncel Graf Icin Bipartite Kontrolu:\n");
    bipartiteKontrol(matris, 1);

    return 0;
}
