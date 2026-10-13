# Hafta 5: Hastane Hasta Takip Sistemi

Bu calismada, bir hastanenin hasta kabul ve muayene sureclerini simule eden dijital takip sistemi C programlama dili ile gelistirilmistir.

## Kullanilan Veri Yapilari ve Mantik

1. **Kuyruk (Queue) - FIFO (First In First Out):**
   * Hastaneye gelen hastalar gelis sirasina gore kuyrugun sonuna eklenir (`enqueue`).
   * Muayene zamani gelen hasta kuyrugun basindan cikarilir (`dequeue`).
   * Durum: `bekliyor`

2. **Yigin (Stack) - LIFO (Last In First Out):**
   * Muayene odasina alinan hasta yigina eklenir (`push`).
   * Muayenesi tamamlanan hasta yigindan cikarilir (`pop`).
   * Durum: `muayenede`

3. **Bagli Liste (Linked List):**
   * Muayenesi biten hastalar tamamlanma sirasina gore bagli listenin sonuna eklenerek gecmis hasta kayitlari olusturulur (`gecmisEkle`).
   * Durum: `tamamlandi`

## Dosyalar

* `soru1.c`: Tum veri yapilarini ve odev senaryosunu iceren C kaynak kodu.
* `5.HaftaOdevSorusu.pdf`: Odev soru metni ve gereksinimleri.
* `cikti.png`: Programin calisma anina ait konsol ekran goruntusu.

## Nasil Calistirilir?

Terminal veya komut satirinda `hafta5` klasorune gidip su komutlari calistirabilirsiniz:

```bash
gcc soru1.c -o soru1
./soru1
```

## Beklenen Ekran Ciktisi

```text
=== Tum Islemler Sonrasi ===
--- Bekleyen Hastalar ---
Hasta ID: 3, Isim: Ayse, Durum: bekliyor
--- Muayene Odasindaki Hastalar ---
Hasta yok.
--- Tamamlanan Hastalar ---
Hasta ID: 1, Isim: Ahmet, Durum: tamamlandi
Hasta ID: 2, Isim: Mehmet, Durum: tamamlandi
```
