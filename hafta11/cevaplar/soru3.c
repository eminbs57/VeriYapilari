#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_COURSES 6
#define MAX_STUDENTS 4

const char *courseNames[NUM_COURSES] = {"d0", "d1", "d2", "d3", "d4", "d5"};

// Dugum bilgilerini ve derecesini tutan yapi
typedef struct
{
    int id;
    int degree;
    int color; // Oturum numarasi (1, 2, 3...)
} Node;

// Komsuluk matrisini sifirlama
void matrisSifirla(int adj[NUM_COURSES][NUM_COURSES])
{
    for (int i = 0; i < NUM_COURSES; i++)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            adj[i][j] = 0;
        }
    }
}

// 1. Cakisma Grafi Modeli: Ogrenci ders listelerinden otomatik matris olusturma
void cakismaGrafiOlustur(int studentCourses[MAX_STUDENTS][NUM_COURSES],
                         int courseCounts[MAX_STUDENTS],
                         int adj[NUM_COURSES][NUM_COURSES])
{
    matrisSifirla(adj);

    for (int s = 0; s < MAX_STUDENTS; s++)
    {
        int count = courseCounts[s];
        // Ayni ogrencinin aldigi tum ders ciftleri arasina kenar ekle
        for (int i = 0; i < count; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                int u = studentCourses[s][i];
                int v = studentCourses[s][j];
                adj[u][v] = 1;
                adj[v][u] = 1;
            }
        }
    }
}

// Matrisi ekrana basma fonksiyonu
void matrisYazdir(int adj[NUM_COURSES][NUM_COURSES])
{
    printf("     ");
    for (int j = 0; j < NUM_COURSES; j++)
    {
        printf(" %-2s ", courseNames[j]);
    }
    printf("\n    +-------------------------\n");
    for (int i = 0; i < NUM_COURSES; i++)
    {
        printf(" %-2s |", courseNames[i]);
        for (int j = 0; j < NUM_COURSES; j++)
        {
            printf("  %d ", adj[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Welch-Powell Renklendirme ve Oturum Planlama Algoritmasi
int welchPowell(int adj[NUM_COURSES][NUM_COURSES], Node nodes[NUM_COURSES])
{
    // 1. Dereceleri hesapla
    for (int i = 0; i < NUM_COURSES; i++)
    {
        nodes[i].id = i;
        nodes[i].color = 0; // Henuz boyanmadi
        nodes[i].degree = 0;
        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (adj[i][j] == 1)
            {
                nodes[i].degree++;
            }
        }
    }

    // 2. Dugumleri derecelerine gore buyukten kucuge sirala (Secmeli / Bubble siralama)
    for (int i = 0; i < NUM_COURSES - 1; i++)
    {
        for (int j = i + 1; j < NUM_COURSES; j++)
        {
            if (nodes[j].degree > nodes[i].degree)
            {
                Node temp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = temp;
            }
        }
    }

    printf("Dugumlerin Derece Siralamasi (Buyukten Kucuge):\n");
    for (int i = 0; i < NUM_COURSES; i++)
    {
        printf("  %s (Derece: %d)\n", courseNames[nodes[i].id], nodes[i].degree);
    }
    printf("\n");

    // 3. Renklendirme islemi (Welch-Powell)
    int currentColor = 0;
    int coloredCount = 0;

    while (coloredCount < NUM_COURSES)
    {
        currentColor++; // Yeni oturum / renk baslat

        // Bu renge atanacak dugumleri tutan gecici liste
        int sessionNodes[NUM_COURSES];
        int sessionCount = 0;

        for (int i = 0; i < NUM_COURSES; i++)
        {
            if (nodes[i].color == 0) // Boyanmamis ise
            {
                // Bu oturuma daha once eklenmis olan derslerle cakismasi var mi?
                bool conflict = false;
                for (int s = 0; s < sessionCount; s++)
                {
                    int assigned = sessionNodes[s];
                    if (adj[nodes[i].id][assigned] == 1)
                    {
                        conflict = true;
                        break;
                    }
                }

                // Eger bu oturumdaki hicbir dersle komsulugu (cakismasi) yoksa boya
                if (!conflict)
                {
                    nodes[i].color = currentColor;
                    sessionNodes[sessionCount++] = nodes[i].id;
                    coloredCount++;
                }
            }
        }
    }

    return currentColor; // Kromatik sayi (Toplam Oturum Sayisi)
}

// 3. Raporlama Fonksiyonu
void oturumlariRaporla(Node nodes[NUM_COURSES], int chromaticNumber)
{
    printf("--- 3. Sinav Oturumlari Raporu ---\n");
    printf("Gerekli Minimum Sinav Oturumu Sayisi (Kromatik Sayi): %d\n\n", chromaticNumber);

    for (int c = 1; c <= chromaticNumber; c++)
    {
        printf("Oturum %d (Ayni anda yapilabilecek sinavlar): { ", c);
        for (int i = 0; i < NUM_COURSES; i++)
        {
            if (nodes[i].color == c)
            {
                printf("%s ", courseNames[nodes[i].id]);
            }
        }
        printf("}\n");
    }
    printf("\n");
}

int main(void)
{
    printf("====================================================================\n");
    printf("     VERI YAPILARI - HAFTA 11: SORU 3 (WELCH-POWELL SINAV TAKVIMI)  \n");
    printf("====================================================================\n\n");

    // Ilk Durum: Ogrenci ders kayit listesi
    // Ogrenci-1: d0 (0), d1 (1), d4 (4)
    // Ogrenci-2: d0 (0), d2 (2), d4 (4)
    // Ogrenci-3: d2 (2), d3 (3), d5 (5)
    // Ogrenci-4: d3 (3), d4 (4), d5 (5)
    int studentCourses[MAX_STUDENTS][NUM_COURSES] = {
        {0, 1, 4}, // Ogrenci 1
        {0, 2, 4}, // Ogrenci 2
        {2, 3, 5}, // Ogrenci 3
        {3, 4, 5}  // Ogrenci 4
    };
    int courseCounts[MAX_STUDENTS] = {3, 3, 3, 3};

    int adj[NUM_COURSES][NUM_COURSES];
    Node nodes[NUM_COURSES];

    printf("--- GOREV 1: Otomatik Cakisma Grafi Modeli (Komsuluk Matrisi) ---\n");
    cakismaGrafiOlustur(studentCourses, courseCounts, adj);
    matrisYazdir(adj);

    printf("--- GOREV 2: Welch-Powell Renklendirme Algoritmasi ---\n");
    int chromaticNumber = welchPowell(adj, nodes);

    // GOREV 3: Raporlama
    oturumlariRaporla(nodes, chromaticNumber);

    // GOREV 4: Dinamik Guncelleme Testi (Ogrenci-4 d4 dersini birakiyor)
    printf("====================================================================\n");
    printf("--- GOREV 4: Dinamik Guncelleme Testi ---\n");
    printf("Senaryo: Ogrenci-4, d4 dersini sistemden birakiyor!\n");
    printf("====================================================================\n\n");

    // Ogrenci 4 artik sadece d3 ve d5 aliyor (d4 cikarildi)
    studentCourses[3][0] = 3;
    studentCourses[3][1] = 5;
    courseCounts[3] = 2;

    cakismaGrafiOlustur(studentCourses, courseCounts, adj);
    printf("Guncel Cakisma Komsuluk Matrisi:\n");
    matrisYazdir(adj);

    printf("Guncel Welch-Powell Renklendirme:\n");
    int newChromaticNumber = welchPowell(adj, nodes);

    printf("--- Guncel Sinav Oturumlari Raporu ---\n");
    oturumlariRaporla(nodes, newChromaticNumber);

    printf("ANALIZ VE DEGERLENDIRME:\n");
    printf("Ogrenci-4'un d4 dersini birakmasiyla (d3, d4) ve (d4, d5) cakismalari ortadan kalkti.\n");
    printf("Boylece {d2, d3, d4, d5} arasindaki 4'lu klik (K4 bileseni) bozuldu.\n");
    printf("Kromatik sayi %d degerinden %d degerine DUSTU! (1 oturum tasarrufu saglandi).\n\n",
           chromaticNumber, newChromaticNumber);

    return 0;
}
