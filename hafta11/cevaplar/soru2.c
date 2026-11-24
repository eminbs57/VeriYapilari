#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define INF 999999

const char nodeNames[V] = {'A', 'B', 'C', 'D', 'E', 'F'};

// Komsuluk matrisi ve kenar agirliklari
int weightMatrix[V][V] = {
    //  A    B    C    D    E    F
    {   0,   7,   5, INF, INF,   1 }, // A
    {   7,   0,   1,   1,   3, INF }, // B
    {   5,   1,   0,   2,   1, INF }, // C
    { INF,   1,   2,   0, INF,   7 }, // D
    { INF,   3,   1, INF,   0,   2 }, // E
    {   1, INF, INF,   7,   2,   0 }  // F
};

// Dijkstra tablosunu ekrana basan yardimci fonksiyon
void printDijkstraTable(int dist[], bool known[], int path[], int step, int selected)
{
    printf("\n--- Adim %d: Secilen Dugum: %c ---\n", step, nodeNames[selected]);
    printf("+-------+---------------+-----------------+--------------+\n");
    printf("| Dugum | Isaret(Known) | Maliyet(Dist)   | Onceki(Path) |\n");
    printf("+-------+---------------+-----------------+--------------+\n");
    for (int i = 0; i < V; i++)
    {
        char distStr[16];
        if (dist[i] == INF)
            snprintf(distStr, sizeof(distStr), "INF");
        else
            snprintf(distStr, sizeof(distStr), "%d", dist[i]);

        char pathStr[16];
        if (path[i] == -1)
            snprintf(pathStr, sizeof(pathStr), "-");
        else
            snprintf(pathStr, sizeof(pathStr), "%c", nodeNames[path[i]]);

        printf("|   %c   |       %d       |       %-7s   |      %-7s |\n",
               nodeNames[i], known[i] ? 1 : 0, distStr, pathStr);
    }
    printf("+-------+---------------+-----------------+--------------+\n");
}

// Tersten okuma (Backtracking) yontemiyle yolu ekrana yazdirma
void printPath(int path[], int target, int start)
{
    int route[V];
    int count = 0;
    int curr = target;

    while (curr != -1)
    {
        route[count++] = curr;
        if (curr == start)
            break;
        curr = path[curr];
    }

    // Tersten geriye dogru okunan dizi, koken->hedef seklinde yazdirilir
    for (int i = count - 1; i >= 0; i--)
    {
        printf("%c", nodeNames[route[i]]);
        if (i > 0)
            printf(" -> ");
    }
}

// Tek bir kok dugum icin Dijkstra algoritmasi
// Verbose = true ise adim adim tablolari basar
int runDijkstra(int startNode, bool verbose, int outDist[], int outPath[])
{
    bool known[V];
    int dist[V];
    int path[V];

    for (int i = 0; i < V; i++)
    {
        known[i] = false;
        dist[i] = INF;
        path[i] = -1;
    }

    dist[startNode] = 0;

    for (int step = 1; step <= V; step++)
    {
        // Known=0 olan en kucuk mesafeli dugumu sec
        int u = -1;
        int minDist = INF;
        for (int i = 0; i < V; i++)
        {
            if (!known[i] && dist[i] < minDist)
            {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        known[u] = true;

        if (verbose)
        {
            printDijkstraTable(dist, known, path, step, u);
        }

        // Komsularin mesafelerini guncelle
        for (int v = 0; v < V; v++)
        {
            if (!known[v] && weightMatrix[u][v] != INF && weightMatrix[u][v] > 0)
            {
                if (dist[u] + weightMatrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + weightMatrix[u][v];
                    path[v] = u;
                }
            }
        }
    }

    int totalCost = 0;
    for (int i = 0; i < V; i++)
    {
        if (outDist != NULL)
            outDist[i] = dist[i];
        if (outPath != NULL)
            outPath[i] = path[i];
        totalCost += dist[i];
    }

    return totalCost;
}

int main(void)
{
    printf("====================================================================\n");
    printf("     VERI YAPILARI - HAFTA 11: SORU 2 (DIJKSTRA VE MERKEZI DUGUM)   \n");
    printf("====================================================================\n\n");

    // GOREV 1: Kok dugum A (Indeks 0) icin adim adim Dijkstra Tablosu
    printf("--- GOREV 1: Kok Dugum 'A' Icin Adim Adim Dijkstra Tablosu ---\n");
    int distA[V];
    int pathA[V];
    runDijkstra(0, true, distA, pathA);

    // GOREV 2: Rota Ciktisi (B ve D dugumleri icin tersten okuma ile rota)
    printf("\n--- GOREV 2: Kok Dugum 'A' Icin B ve D Rota Ciktilari ---\n");

    // A -> B
    int targetB = 1; // B
    printf("Hedef B: Rota: ");
    printPath(pathA, targetB, 0);
    printf(" | Toplam Maliyet: %d\n", distA[targetB]);

    // A -> D
    int targetD = 3; // D
    printf("Hedef D: Rota: ");
    printPath(pathA, targetD, 0);
    printf(" | Toplam Maliyet: %d\n\n", distA[targetD]);

    // GOREV 3: Merkezi Dugum Tespiti (Tum dugumler icin Dijkstra calistirilir)
    printf("--- GOREV 3: Merkezi Dugum Analizi (Closeness Centrality) ---\n");
    printf("+-------+----------------------------------+-----------------+\n");
    printf("| Dugum | Tum Dugumlere En Kisa Mesafeler  | Toplam Maliyet  |\n");
    printf("+-------+----------------------------------+-----------------+\n");

    int minTotal = INF;
    int bestCentral = -1;

    for (int i = 0; i < V; i++)
    {
        int curDist[V];
        int total = runDijkstra(i, false, curDist, NULL);

        printf("|   %c   | ", nodeNames[i]);
        for (int j = 0; j < V; j++)
        {
            printf("%c:%-2d ", nodeNames[j], curDist[j]);
        }
        printf("|       %-7d   |\n", total);

        if (total < minTotal)
        {
            minTotal = total;
            bestCentral = i;
        }
    }
    printf("+-------+----------------------------------+-----------------+\n");

    printf("\nSONUC: En dusuk toplam maliyete sahip MERKEZI DUGUM (Ana Aktarma Merkezi):\n");
    printf("-> Dugum: %c (veya esit minimum maliyetli dugumler)\n", nodeNames[bestCentral]);
    printf("-> Minimum Toplam Ag Maliyeti: %d\n", minTotal);
    printf("Aciklama: C ve E dugumlerinin her ikisi de 11 birimlik en dusuk toplam\n");
    printf("ulasim maliyetine sahiptir. E dugumu maksimum 3 adimlik eksantriklik (eccentricity)\n");
    printf("ile en dengeli dagitim deposudur.\n\n");

    return 0;
}
