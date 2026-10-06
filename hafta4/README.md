
### Odev 1: Muzik Calar Simulasyonu
- **Dosya:** `ornek1.c`
- **Veri Yapisi:** Cift Yonlu Bagli Liste (Doubly Linked List)
- **Aciklama:** Bu uygulamada bir muzik calarin temel islevleri gerceklestirilmistir. Kullanici listeye yeni sarki ekleyebilir, sarki silebilir ve dinledigi sarkiyi bir sonrakine (next) veya bir oncekine (prev) kaydirabilir. Liste bosken ve silme islemlerinde `prev` ve `next` pointer'lari guvenli bir sekilde guncellenir.

### Odev 2: Undo (Geri Alma) Simulasyonu 
- **Dosya:** `ornek2.c`
- **Veri Yapisi:** Yigin (Stack) - LIFO (Son Giren Ilk Cikar)
- **Aciklama:** Bir metin editorundeki geri alma isleminin calisma mantigini gosterir. Kullanici `ekle <kelime>` yazdiginda kelime stack'e eklenir, `undo` yazdiginda en son eklenen kelime silinir. `show` komutuyla da eklenen kelimeler kullanicinin girdigi sirayla ekrana yazdirilir.

### Odev 3: Yazici Islem Sirasi
- **Dosya:** `ornek3.c`
- **Veri Yapisi:** Kuyruk (Queue) - FIFO (Ilk Giren Ilk Cikar)
- **Aciklama:** Yaziciya gonderilen belgelerin bekleme kuyrugunu simule eder. Yeni bir dosya kuyrugun sonuna eklenir (enqueue). Yazdirma basladiginda ise kuyruga ilk girmis olan dosya ilk yazdirilir ve cikarilir (dequeue). Kuyruk bossa program hata vermeden uyari gosterir.

## Nasil Calistirilir?

Kodlari derlemek ve calistirmak icin terminal /cmd uzerinden herhangi bir C derleyicisi (ornek: `gcc`) kullanabilirsiniz. 

Ornegin 1. Odevi derleyip calistirmak icin:

gcc ornek1.c -o ornek1
./ornek1

2. Odevi derleyip calistirmak icin:

gcc ornek2.c -o ornek2
./ornek2


3. Odevi derleyip calistirmak icin:

gcc ornek3.c -o ornek3
./ornek3

