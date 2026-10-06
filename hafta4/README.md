Odev 1: Muzik Calar Simulasyonu
Dosya: muzik_calar.c
Veri Yapisi: Cift Yonlu Bagli Liste (Doubly Linked List)
Aciklama: Bu uygulamada bir muzik calarin temel islevleri gerceklestirilmistir. Kullanici listeye yeni sarki ekleyebilir, sarki silebilir ve dinledigi sarkiyi bir sonrakine (next) veya bir oncekine (prev) kaydirabilir. Liste bosken ve silme islemlerinde prev ve next pointer'lari guvenli bir sekilde guncellenir.
Odev 2: Undo (Geri Alma) Simulasyonu
Dosya: undo_simulasyonu.c
Veri Yapisi: Yigin (Stack) - LIFO (Son Giren Ilk Cikar)
Aciklama: Bir metin editorundeki geri alma isleminin calisma mantigini gosterir. Kullanici ekle <kelime> yazdiginda kelime stack'e eklenir, undo yazdiginda en son eklenen kelime silinir. show komutuyla da eklenen kelimeler kullanicinin girdigi sirayla ekrana yazdirilir.
Odev 3: Yazici Islem Sirasi
Dosya: yazici_kuyrugu.c
Veri Yapisi: Kuyruk (Queue) - FIFO (Ilk Giren Ilk Cikar)
Aciklama: Yaziciya gonderilen belgelerin bekleme kuyrugunu simule eder. Yeni bir dosya kuyrugun sonuna eklenir (enqueue). Yazdirma basladiginda ise kuyruga ilk girmis olan dosya ilk yazdirilir ve cikarilir (dequeue). Kuyruk bossa program hata vermeden uyari gosterir.
Nasil Calistirilir?
Kodlari derlemek ve calistirmak icin terminal (veya komut istemcisi) uzerinden herhangi bir C derleyicisi (ornek: gcc) kullanabilirsiniz.

Ornegin 1. Odevi derleyip calistirmak icin:

bash

gcc muzik_calar.c -o muzik
./muzik
Odevi derleyip calistirmak icin:
bash

gcc undo_simulasyonu.c -o undo
./undo
Odevi derleyip calistirmak icin:
gcc yazici_kuyrugu.c -o yazici
./yazici
