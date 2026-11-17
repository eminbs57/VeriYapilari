#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VERTEX_COUNT 5

// Şehir bilgileri
const char *cityNames[VERTEX_COUNT] = {
    "Istanbul", // A (Indis 0)
    "Ankara",   // B (Indis 1)
    "Izmir",    // C (Indis 2)
    "Bursa",    // D (Indis 3)
    "Antalya"   // E (Indis 4)
};

const char cityCodes[VERTEX_COUNT] = {'A', 'B', 'C', 'D', 'E'};

// Ziyaret sırasını kaydetmek için sayaç ve dizi
int visitOrder[VERTEX_COUNT];
int orderCount = 0;

// Özyinelemeli Derinlik Öncelikli Arama (Recursive DFS)
void dfsRecursive(int adjMatrix[VERTEX_COUNT][VERTEX_COUNT], int current, bool visited[], int depth)
{
    // Düğümü ziyaret et ve kaydet
    visited[current] = true;
    visitOrder[orderCount++] = current;

    // Girintili adım açıklaması
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("[Ziyaret]: %c (%s) kesfedildi.\n", cityCodes[current], cityNames[current]);

    // Komşuları alfabetik / indis sırasıyla incele
    for (int neighbor = 0; neighbor < VERTEX_COUNT; neighbor++)
    {
        if (adjMatrix[current][neighbor] == 1)
        {
            if (!visited[neighbor])
            {
                for (int i = 0; i < depth; i++)
                    printf("  ");
                printf("  -> %c (%s) dugumune derinlemesine ilerleniyor...\n",
                       cityCodes[neighbor], cityNames[neighbor]);

                dfsRecursive(adjMatrix, neighbor, visited, depth + 1);

                for (int i = 0; i < depth; i++)
                    printf("  ");
                printf("  <- %c (%s) tamamlandi, %c (%s) dugumune geri donuldu (Backtrack).\n",
                       cityCodes[neighbor], cityNames[neighbor],
                       cityCodes[current], cityNames[current]);
            }
            else
            {
                for (int i = 0; i < depth; i++)
                    printf("  ");
                printf("  -- %c (%s) zaten ziyaret edilmis (Atlandi).\n",
                       cityCodes[neighbor], cityNames[neighbor]);
            }
        }
    }
}

// DFS Başlatıcı Fonksiyon
void dfs(int adjMatrix[VERTEX_COUNT][VERTEX_COUNT], int startNode)
{
    bool visited[VERTEX_COUNT] = {false};
    orderCount = 0;

    printf("====================================================\n");
    printf("         DFS (Derinlik Oncelikli Arama)            \n");
    printf("====================================================\n");
    printf("Baslangic Sehri: %c - %s\n\n", cityCodes[startNode], cityNames[startNode]);

    printf("Calisma ve Geri Izleme (Backtracking) Adimlari:\n");
    dfsRecursive(adjMatrix, startNode, visited, 0);

    // Nihai Ziyaret Sırasını Yazdır
    printf("\n====================================================\n");
    printf("DFS Nihai Ziyaret Sirasi:\n");
    for (int i = 0; i < orderCount; i++)
    {
        printf("%c (%s)", cityCodes[visitOrder[i]], cityNames[visitOrder[i]]);
        if (i < orderCount - 1)
        {
            printf(" -> ");
        }
    }
    printf("\n====================================================\n");
}

int main(void)
{
    // 5 Düğümlü Komşuluk Matrisi (Adjacency Matrix)
    // 0: A (Istanbul), 1: B (Ankara), 2: C (Izmir), 3: D (Bursa), 4: E (Antalya)
    //
    // Bağlantılar:
    // A - B (Istanbul - Ankara)
    // A - D (Istanbul - Bursa)
    // B - C (Ankara - Izmir)
    // B - E (Ankara - Antalya)
    // D - E (Bursa - Antalya)
    int adjMatrix[VERTEX_COUNT][VERTEX_COUNT] = {
        /* A: Ist */ {0, 1, 0, 1, 0},
        /* B: Ank */ {1, 0, 1, 0, 1},
        /* C: Izm */ {0, 1, 0, 0, 0},
        /* D: Bur */ {1, 0, 0, 0, 1},
        /* E: Ant */ {0, 1, 0, 1, 0}};

    // A (İstanbul / Indis 0) başlangıç düğümü ile DFS çalıştır
    dfs(adjMatrix, 0);

    return 0;
}
