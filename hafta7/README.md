#  Hazine Ağacı Oyunu

İkili Arama Ağacı (Binary Search Tree - BST) veri yapısı kullanılarak C dilinde geliştirilmiş interaktif bir arama ve keşif oyunu.

Kullanıcı belirli bir sayıyı arayarak ağaçta kazı yapar; sayı ağaçta mevcutsa hazine bulunur, aksi halde kazı boş çıkar.

---

##  Özellikler

- **İkili Arama Ağacı (BST):** Dinamik bellek yönetimi (`malloc`) ve işaretçiler (pointers) ile oluşturulmuş ağaç yapısı.
- **Rekürsif Arama:** Aranan hazine değeri ağaç üzerinde özyinelemeli (recursive) olarak kontrol edilir.
- **Adım Takibi (Trace):** Arama esnasında kökten başlayarak ziyaret edilen tüm düğümler adım adım ekrana yazdırılır.
- **En Kötü Durum Analizi (Ağaç Yüksekliği):** Ağacın maksimum derinliği hesaplanarak hazineyi bulmak için gereken en kötü durum adım sayısı kullanıcıya sunulur.

---

##  Kullanılan Teknolojiler ve Kavramlar

- **Dil:** C
- **Veri Yapısı:** İkili Arama Ağacı (Binary Search Tree)
- **Kavramlar:**
  - Dynamic Memory Allocation (`malloc`, `free`)
  - Struct & Pointers
  - Recursion (Özyineleme)
  - Ağaç Yüksekliği (Tree Height / Depth Calculation)

---

##  Nasıl Derlenir ve Çalıştırılır?

Projeyi GCC derleyicisi kullanarak terminal üzerinden çalıştırabilirsiniz:

```bash
# 1. Kaynak kodu derleyin
gcc main.c -o hazine_agaci

# 2. Programı çalıştırın
./hazine_agaci
```

_(Windows kullanıyorsanız `hazine_agaci.exe` şeklinde çalıştırabilirsiniz.)_

---

##  Örnek Ekran Çıktıları

### Durum 1: Hazine Bulunduğunda

```text
=== HAZINE AGACI OYUNUNA HOS GELDINIZ ===

Bilgi: Hazineyi bulmak icin en kotu durumda 3 adim gerekir (Agac Yuksekligi).

Hazine aramak icin bir sayi kazin (girin): 40

Kazma islemi basladi (Arama adimlari):
-> Ziyaret edilen dugum: 50
-> Ziyaret edilen dugum: 30
-> Ziyaret edilen dugum: 40

Hazine bulundu!
```

### Durum 2: Hazine Bulunamadığında

```text
=== HAZINE AGACI OYUNUNA HOS GELDINIZ ===

Bilgi: Hazineyi bulmak icin en kotu durumda 3 adim gerekir (Agac Yuksekligi).

Hazine aramak icin bir sayi kazin (girin): 90

Kazma islemi basladi (Arama adimlari):
-> Ziyaret edilen dugum: 50
-> Ziyaret edilen dugum: 70
-> Ziyaret edilen dugum: 80

Bosuna kazdin!
```
