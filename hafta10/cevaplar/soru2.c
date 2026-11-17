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

// BFS için Basit Kuyruk (Queue - FIFO) Yapısı
typedef struct
{
    int items[VERTEX_COUNT];
    int front;
    int rear;
} Queue;

// Kuyruk ilklendirme
void initQueue(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

// Kuyruk boş mu?
bool isQueueEmpty(Queue *q)
{
    return q->front == -1;
}

// Kuyruğa eleman ekleme (Enqueue)
void enqueue(Queue *q, int value)
{
    if (q->rear == VERTEX_COUNT - 1)
    {
        return; // Kuyruk dolu
    }
    if (q->front == -1)
    {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

// Kuyruktan eleman çıkarma (Dequeue)
int dequeue(Queue *q)
{
    if (isQueueEmpty(q))
    {
        return -1;
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
    return item;
}

// Kuyruğun anlık durumunu ekrana yazdırma
void printQueue(Queue *q)
{
    printf("  [Kuyruk]: ");
    if (isQueueEmpty(q))
    {
        printf("(Bos)\n");
        return;
    }
    for (int i = q->front; i <= q->rear; i++)
    {
        printf("%c (%s)", cityCodes[q->items[i]], cityNames[q->items[i]]);
        if (i < q->rear)
            printf(" -> ");
    }
    printf("\n");
}

// Genişlik Öncelikli Arama (Breadth-First Search - BFS)
void bfs(int adjMatrix[VERTEX_COUNT][VERTEX_COUNT], int startNode)
{
    bool visited[VERTEX_COUNT] = {false};
    Queue q;
    initQueue(&q);

    // Ziyaret sırasını kaydetmek için dizi
    int visitOrder[VERTEX_COUNT];
    int orderCount = 0;

    printf("====================================================\n");
    printf("         BFS (Genislik Oncelikli Arama)            \n");
    printf("====================================================\n");
    printf("Baslangic Sehri: %c - %s\n\n", cityCodes[startNode], cityNames[startNode]);

    // Başlangıç düğümünü işaretle ve kuyruğa ekle
    visited[startNode] = true;
    enqueue(&q, startNode);

    int step = 1;

    while (!isQueueEmpty(&q))
    {
        printf("--- Adim %d ---\n", step++);
        printQueue(&q);

        int current = dequeue(&q);
        visitOrder[orderCount++] = current;

        printf("  Ziyaret Edilen: %c (%s)\n", cityCodes[current], cityNames[current]);

        // Komşuları alfabetik / indis sırasıyla incele
        for (int neighbor = 0; neighbor < VERTEX_COUNT; neighbor++)
        {
            if (adjMatrix[current][neighbor] == 1 && !visited[neighbor])
            {
                visited[neighbor] = true;
                enqueue(&q, neighbor);
                printf("    -> Komsusu %c (%s) kuyruga eklendi.\n",
                       cityCodes[neighbor], cityNames[neighbor]);
            }
        }
        printf("\n");
    }

    // Nihai Ziyaret Sırasını Yazdır
    printf("====================================================\n");
    printf("BFS Nihai Ziyaret Sirasi:\n");
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
        /* E: Ant */ {0, 1, 0, 1, 0}
    };

    // A (İstanbul / Indis 0) başlangıç düğümü ile BFS çalıştır
    bfs(adjMatrix, 0);

    return 0;
}
