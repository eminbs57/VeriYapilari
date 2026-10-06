#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stack icin
typedef struct Word
{
    char text[50];
    struct Word *next;
} Word;

void pushWord(Word **top, char *text);
void popWord(Word **top);
void showWords(Word *top);

// stacke kelime ekleme (basa eklenir)
void pushWord(Word **top, char *text)
{
    Word *newWord = (Word *)malloc(sizeof(Word));
    if (newWord == NULL)
    {
        printf("Yer yok!\n");
        return;
    }

    strcpy(newWord->text, text);
    newWord->next = *top;
    *top = newWord; // yeni kelime en uste   geldi
}

// stackten kelime cikarma (geri alma)
void popWord(Word **top)
{
    if (*top == NULL)
    {
        // zaten bossa silecek bir sey yok
        return;
    }

    Word *temp = *top;
    *top = (*top)->next; // bir sonrakini yeni top yapiyoruz

    free(temp); // sildigimiz kelimeyi hafizadan atiyoruz
}

// ekrana yazdirma
void showWords(Word *top)
{
    if (top == NULL)
    {
        printf("-> \n");
        return;
    }

    // kelimeler stackte ters durdugu (son giren ilk cikar) icin
    // ekrana "Merhaba Dunya" sirasiyla yazdirabilmek amaciyla
    // once gecici bir diziye alip tersten yazdiracagiz

    char kelimeler[100][50];
    int sayac = 0;

    Word *temp = top;
    while (temp != NULL)
    {
        strcpy(kelimeler[sayac], temp->text);
        sayac++;
        temp = temp->next;
    }

    printf("-> ");
    // diziyi tersten yazdirinca ilk girilen ilk gosterilmis oluyor
    for (int i = sayac - 1; i >= 0; i--)
    {
        printf("%s ", kelimeler[i]);
    }
    printf("\n");
}

int main()
{
    Word *top = NULL;
    char komut[20];
    char kelime[50];

    printf("Kullanim ornegi:\n");
    printf("> ekle Merhaba\n");
    printf("> undo\n");
    printf("> show\n");
    printf("> exit\n\n");

    while (1)
    {
        printf("> ");
        scanf("%s", komut);

        if (strcmp(komut, "ekle") == 0)
        {
            // eger add yazildiysa yanindaki kelimeyi de okuyoruz
            scanf("%s", kelime);
            pushWord(&top, kelime);
        }
        else if (strcmp(komut, "undo") == 0)
        {
            popWord(&top);
        }
        else if (strcmp(komut, "show") == 0)
        {
            showWords(top);
        }
        else if (strcmp(komut, "exit") == 0)
        {
            break; // donguden cik
        }
        else
        {
            printf("Yanlis komut girdiniz.\n");
            // ekstradan girilen seyleri yutmasi icin
            while (getchar() != '\n')
                ;
        }
    }

    return 0;
}
