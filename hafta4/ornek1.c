#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song
{
    char name[50];
    struct Song *next;
    struct Song *prev;
} Song;

void addSongToEnd(Song **head, char *name);
void removeSong(Song **head, char *name);
void playNext(Song **current);
void playPrevious(Song **current);
void displayPlaylist(Song *head);

// yeni sarki ekle
void addSongToEnd(Song **head, char *name)
{
    // yeni sarki icin yer ayir
    Song *newSong = (Song *)malloc(sizeof(Song));
    if (newSong == NULL)
    {
        printf("Yer bulunamadi!\n");
        return;
    }

    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    // liste bossa head bu sarki olsun
    if (*head == NULL)
    {
        *head = newSong;
        return;
    }

    // bos degilse en sona git
    Song *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    // sona ekle
    temp->next = newSong;
    newSong->prev = temp;
}

// sarki silme fonksiyonu
void removeSong(Song **head, char *name)
{
    if (*head == NULL)
    {
        printf("Liste bos.\n");
        return;
    }

    Song *temp = *head;

    // silinecek sarkiyi ariyoruz
    while (temp != NULL && strcmp(temp->name, name) != 0)
    {
        temp = temp->next;
    }

    // bulamadiysak
    if (temp == NULL)
    {
        printf("Sarki bulunamadi.\n");
        return;
    }

    // sarkiyi bulduk simdi cikaracagiz

    // eger oncesinde sarki varsa
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    else
    {
        // yoksa demek ki ilk sarkiyi siliyoruz
        *head = temp->next;
    }

    // eger sonrasinda sarki varsa
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    free(temp); // hafizayi temizle
    printf("%s silindi.\n", name);
}

// ileri sar
void playNext(Song **current)
{
    if (*current == NULL)
    {
        printf("Liste bos.\n");
        return;
    }

    if ((*current)->next != NULL)
    {
        *current = (*current)->next;
        printf("Su an caliyor: %s\n", (*current)->name);
    }
    else
    {
        printf("Listenin sonundasiniz.\n");
    }
}

// geri sar
void playPrevious(Song **current)
{
    if (*current == NULL)
    {
        printf("Liste bos.\n");
        return;
    }

    if ((*current)->prev != NULL)
    {
        *current = (*current)->prev;
        printf("Su an caliyor: %s\n", (*current)->name);
    }
    else
    {
        printf("Listenin basindasiniz.\n");
    }
}

// listeyi ekrana yazdir
void displayPlaylist(Song *head)
{
    if (head == NULL)
    {
        printf("Liste bos.\n");
        return;
    }

    printf("\n--- Calma Listesi ---\n");
    Song *temp = head;
    while (temp != NULL)
    {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }
    printf("---------------------\n");
}

int main()
{
    Song *head = NULL;
    Song *current = NULL; // su an calan sarki
    int secim;
    char isim[50];

    while (1)
    {
        // basit bir menu
        printf("\n--- Muzik Calar ---\n");
        printf("1. Sarki Ekle\n");
        printf("2. Sarki Sil\n");
        printf("3. Sonraki Sarkiyi Cal\n");
        printf("4. Onceki Sarkiyi Cal\n");
        printf("5. Listeyi Goster\n");
        printf("6. Calan Sarkiyi Goster\n");
        printf("7. Cikis\n");
        printf("Seciminiz: ");

        scanf("%d", &secim);
        getchar(); // enteri yutmasi icin

        switch (secim)
        {
        case 1:
            printf("Sarki ismi: ");
            fgets(isim, 50, stdin);
            isim[strcspn(isim, "\n")] = '\0'; // sondaki boslugu sil
            addSongToEnd(&head, isim);

            // ilk eklenen sarkiyi current yap
            if (current == NULL)
            {
                current = head;
            }
            break;

        case 2:
            printf("Silinecek sarki ismi: ");
            fgets(isim, 50, stdin);
            isim[strcspn(isim, "\n")] = '\0';

            // eger calan sarkiyi siliyorsak current bozulmasin diye degistiriyoruz
            if (current != NULL && strcmp(current->name, isim) == 0)
            {
                if (current->next != NULL)
                {
                    current = current->next;
                }
                else if (current->prev != NULL)
                {
                    current = current->prev;
                }
                else
                {
                    current = NULL;
                }
            }

            removeSong(&head, isim);
            break;

        case 3:
            playNext(&current);
            break;

        case 4:
            playPrevious(&current);
            break;

        case 5:
            displayPlaylist(head);
            break;

        case 6:
            if (current != NULL)
            {
                printf("Su an caliyor: %s\n", current->name);
            }
            else
            {
                printf("Liste bos.\n");
            }
            break;

        case 7:
            printf("Cikis...\n");
            return 0;

        default:
            printf("Yanlis secim yaptiniz.\n");
        }
    }

    return 0;
}
