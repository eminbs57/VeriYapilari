#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hasta bilgileri struct yapisi
typedef struct
{
    int id;
    char isim[50];
    char durum[20]; // bekliyor, muayenede, tamamlandi
} Hasta;

// 1. kuyruk veri yapisi (FIFO)
typedef struct QueueNode
{
    Hasta data;
    struct QueueNode *next;
} QueueNode;

typedef struct
{
    QueueNode *front; // kuyrugun basi
    QueueNode *rear;  // kuyrugun sonu
} Queue;

// 2. yigin veri yapisi (LIFO)
typedef struct StackNode
{
    Hasta data;
    struct StackNode *next;
} StackNode;

typedef struct
{
    StackNode *top; // yiginin tepesi
} Stack;

// 3. bagli liste veri yapisi (gecmis hastalar)
typedef struct ListNode
{
    Hasta data;
    struct ListNode *next;
} ListNode;

typedef struct
{
    ListNode *head; // listenin basi
} LinkedList;

// kuyrugu baslatma
void initQueue(Queue *q)
{
    q->front = NULL;
    q->rear = NULL;
}

// yigini baslatma
void initStack(Stack *s)
{
    s->top = NULL;
}

// bagli listeyi baslatma
void initList(LinkedList *list)
{
    list->head = NULL;
}

// yeni hasta olusturma yardimci fonksiyonu
Hasta hastaOlustur(int id, const char *isim, const char *durum)
{
    Hasta h;
    h.id = id;
    strncpy(h.isim, isim, sizeof(h.isim) - 1);
    h.isim[sizeof(h.isim) - 1] = '\0';
    strncpy(h.durum, durum, sizeof(h.durum) - 1);
    h.durum[sizeof(h.durum) - 1] = '\0';
    return h;
}

// kuyruk bos mu kontrolu
int isQueueEmpty(Queue *q)
{
    if (q->front == NULL)
    {
        return 1;
    }
    return 0;
}

// kuyrugun sonuna eleman ekleme (enqueue)
void enqueue(Queue *q, Hasta h)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (newNode == NULL)
    {
        printf("Bellek yetersiz!\n");
        return;
    }
    newNode->data = h;
    newNode->next = NULL;

    if (isQueueEmpty(q))
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// kuyrugun basindan eleman cikarma (dequeue)
Hasta dequeue(Queue *q)
{
    Hasta bos = {-1, "", ""};
    if (isQueueEmpty(q))
    {
        printf("Uyari: Kuyruk bos!\n");
        return bos;
    }

    QueueNode *temp = q->front;
    Hasta cikarilan = temp->data;

    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
    return cikarilan;
}

// bekleyen hastalari listeleme
void kuyrukListele(Queue *q)
{
    printf("--- Bekleyen Hastalar ---\n");
    if (isQueueEmpty(q))
    {
        printf("Hasta yok.\n");
        return;
    }

    QueueNode *temp = q->front;
    while (temp != NULL)
    {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n",
               temp->data.id, temp->data.isim, temp->data.durum);
        temp = temp->next;
    }
}

// yigin bos mu kontrolu
int isStackEmpty(Stack *s)
{
    if (s->top == NULL)
    {
        return 1;
    }
    return 0;
}

// yiginin tepesine eleman ekleme (push)
void push(Stack *s, Hasta h)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL)
    {
        printf("Bellek yetersiz!\n");
        return;
    }
    newNode->data = h;
    newNode->next = s->top;
    s->top = newNode;
}

// yigindan eleman cikarma (pop)
Hasta pop(Stack *s)
{
    Hasta bos = {-1, "", ""};
    if (isStackEmpty(s))
    {
        printf("Uyari: Yigin bos!\n");
        return bos;
    }

    StackNode *temp = s->top;
    Hasta cikarilan = temp->data;
    s->top = s->top->next;

    free(temp);
    return cikarilan;
}

// muayene odasindaki hastalari listeleme
void yiginListele(Stack *s)
{
    printf("--- Muayene Odasindaki Hastalar ---\n");
    if (isStackEmpty(s))
    {
        printf("Hasta yok.\n");
        return;
    }

    StackNode *temp = s->top;
    while (temp != NULL)
    {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n",
               temp->data.id, temp->data.isim, temp->data.durum);
        temp = temp->next;
    }
}

// listenin sonuna tamamlanan hastayi ekleme
void gecmisEkle(LinkedList *list, Hasta h)
{
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL)
    {
        printf("Bellek yetersiz!\n");
        return;
    }
    newNode->data = h;
    newNode->next = NULL;

    if (list->head == NULL)
    {
        list->head = newNode;
    }
    else
    {
        ListNode *temp = list->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// tamamlanan hastalari listeleme
void gecmisListele(LinkedList *list)
{
    printf("--- Tamamlanan Hastalar ---\n");
    if (list == NULL || list->head == NULL)
    {
        printf("Hasta yok.\n");
        return;
    }

    ListNode *temp = list->head;
    while (temp != NULL)
    {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n",
               temp->data.id, temp->data.isim, temp->data.durum);
        temp = temp->next;
    }
}

// hastayi muayene odasina alma islemi
void muayeneyeAl(Queue *q, Stack *s)
{
    if (isQueueEmpty(q))
    {
        printf("Uyari: Bekleyen hasta yok!\n");
        return;
    }
    Hasta h = dequeue(q);
    strcpy(h.durum, "muayenede");
    push(s, h);
    printf("Hasta muayene odasina alindi: %s\n", h.isim);
}

// muayeneyi tamamlayip gecmis listesine aktarma islemi
void muayeneTamamla(Stack *s, LinkedList *list)
{
    if (isStackEmpty(s))
    {
        printf("Uyari: Muayene odasinda hasta yok!\n");
        return;
    }
    Hasta h = pop(s);
    strcpy(h.durum, "tamamlandi");
    gecmisEkle(list, h);
    printf("Hasta muayenesi tamamlandi: %s\n", h.isim);
}

// tum listeleri ekrana basma
void tumDurumuYazdir(Queue *q, Stack *s, LinkedList *list, const char *baslik)
{
    printf("%s\n", baslik);
    kuyrukListele(q);
    yiginListele(s);
    gecmisListele(list);
    printf("\n");
}

int main()
{
    Queue beklemeKuyrugu;
    Stack muayeneYigini;
    LinkedList gecmisListesi;

    initQueue(&beklemeKuyrugu);
    initStack(&muayeneYigini);
    initList(&gecmisListesi);

    // 1. adim: hastalar sirayla kuyruga kaydedilir
    printf("1. Adim: Hastalar kuyruga ekleniyor...\n");
    enqueue(&beklemeKuyrugu, hastaOlustur(1, "Ahmet", "bekliyor"));
    enqueue(&beklemeKuyrugu, hastaOlustur(2, "Mehmet", "bekliyor"));
    enqueue(&beklemeKuyrugu, hastaOlustur(3, "Ayse", "bekliyor"));
    printf("Hastalar kaydedildi.\n\n");

    // baslangic durumunu ekrana yazdirma
    tumDurumuYazdir(&beklemeKuyrugu, &muayeneYigini, &gecmisListesi, "=== Baslangic Durumu ===");

    // 2. adim: ahmet muayeneye alinir ve muayenesi tamamlanir
    printf("2. Adim: Ahmet muayeneye aliniyor ve tamamlaniyor...\n");
    muayeneyeAl(&beklemeKuyrugu, &muayeneYigini);
    muayeneTamamla(&muayeneYigini, &gecmisListesi);
    printf("\n");

    // 3. adim: mehmet muayeneye alinir ve muayenesi tamamlanir
    printf("3. Adim: Mehmet muayeneye aliniyor ve tamamlaniyor...\n");
    muayeneyeAl(&beklemeKuyrugu, &muayeneYigini);
    muayeneTamamla(&muayeneYigini, &gecmisListesi);
    printf("\n");

    // 4. adim: ayse bekleme kuyrugunda birakilir
    printf("4. Adim: Ayse bekleme kuyrugunda bekletildi.\n\n");

    // 5. adim: tum islemler sonrasindaki son durum yazdirilir
    tumDurumuYazdir(&beklemeKuyrugu, &muayeneYigini, &gecmisListesi, "=== Tum Islemler Sonrasi ===");

    return 0;
}