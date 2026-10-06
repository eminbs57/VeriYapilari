#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob
{
    char fileName[50];
    struct PrintJob *next;
} PrintJob;

typedef struct Queue
{
    PrintJob *front;
    PrintJob *rear;
} Queue;

// fonksiyon prototipleri
void enqueuePrintJob(Queue *q, char *fileName);
void processNextJob(Queue *q);
void showQueue(Queue q);

// kuyruga yeni dosya ekleme (fifo mantigi - sona eklenir)
void enqueuePrintJob(Queue *q, char *fileName)
{
    PrintJob *newJob = (PrintJob *)malloc(sizeof(PrintJob));
    if (newJob == NULL)
    {
        printf("Yer yok!\n");
        return;
    }

    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;

    // eger kuyruk bossa, hem front hem rear bu yeni eleman olur
    if (q->rear == NULL)
    {
        q->front = newJob;
        q->rear = newJob;
        return;
    }

    // kuyruk bos degilse en arkaya (rear) ekliyoruz
    q->rear->next = newJob;
    q->rear = newJob; // yeni arka elemanimiz bu oldu
}

// kuyruktan siradaki dosyayi yazdirma (bastan cikarilir)
void processNextJob(Queue *q)
{
    // eger kuyruk bossa islem yapma
    if (q->front == NULL)
    {
        printf("Kuyruk bos, yazdirilacak dosya yok.\n");
        return;
    }

    // en bastaki (front) elemani alacagiz
    PrintJob *temp = q->front;

    printf(">>> %s yazdiriliyor...\n", temp->fileName);

    // siradaki elemani yeni bas (front) yapiyoruz
    q->front = q->front->next;

    // eger cikarttigimiz eleman kuyruktaki son elemansa arka (rear) pointeri da bosaltmaliyiz
    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp); // yazdirilan dosyayi hafizadan atiyoruz
}

// kuyrugu gosterme
// dikkat: iskelette Queue* yerine Queue istenmis
// bu yuzden q.front seklinde kullaniyoruz
void showQueue(Queue q)
{
    if (q.front == NULL)
    {
        printf("Kuyruk su an bos.\n");
        return;
    }

    printf("\n--- Yazdirma Kuyrugu ---\n");
    PrintJob *temp = q.front;
    int sira = 1;

    while (temp != NULL)
    {
        printf("%d) %s\n", sira, temp->fileName);
        temp = temp->next;
        sira++;
    }
    printf("------------------------\n");
}

int main()
{
    Queue q;
    // baslangicta kuyruk bos olmali
    q.front = NULL;
    q.rear = NULL;

    int secim;
    char dosya[50];

    while (1)
    {
        printf("\n1) Yeni dosya ekle\n");
        printf("2) Yazdir\n");
        printf("3) Kuyrugu goster\n");
        printf("4) Cikis\n");
        printf("Seciminiz: ");

        scanf("%d", &secim);
        getchar(); // enteri yutmasi icin

        switch (secim)
        {
        case 1:
            printf("Dosya adi: ");
            fgets(dosya, 50, stdin);
            dosya[strcspn(dosya, "\n")] = '\0'; // sondaki enter boslugunu sil
            enqueuePrintJob(&q, dosya);
            printf("%s kuyruga eklendi.\n", dosya);
            break;

        case 2:
            processNextJob(&q);
            break;

        case 3:
            showQueue(q);
            break;

        case 4:
            printf("Cikis yapiliyor...\n");
            return 0;

        default:
            printf("Yanlis secim yaptiniz.\n");
        }
    }

    return 0;
}