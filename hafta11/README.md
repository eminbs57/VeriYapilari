# Hafta 11: İki Parçalı Graflar (Bipartite), En Kısa Yol (Dijkstra) ve Graf Renklendirme (Welch-Powell)

Bu klasör, Veri Yapıları Laboratuvarı **Hafta 11: İki Parçalı Graf Analizi (Bipartite Graph), En Az Maliyetli Yol ve Merkezi Düğüm Analizi (Dijkstra) ile Çakışmasız Sınav Takvimi Oluşturma (Welch-Powell Algoritması)** çalışmasına ait teorik çözümleri, C dili kaynak kodlarını ve program çalışma çıktılarını içermektedir.

---

## İçerik ve Klasör Yapısı

```text
hafta11/
├── hafta11_sorular.pdf               # Laboratuvar föyü ve soru metinleri
├── README.md                         # Hafta 11 dokümantasyonu ve detaylı analizler
├── cevaplar/
│   ├── hafta11_cevaplar.txt          # Tüm soruların ve teorik maddelerin yazılı metin çözümleri
│   ├── soru1.c                       # Soru 1: Komşuluk matrisi, derece hesabı, Bipartite testi ve dinamik test
│   ├── soru2.c                       # Soru 2: Dijkstra tablosu, rota bulma (backtrack) ve merkezi düğüm analizi
│   └── soru3.c                       # Soru 3: Çakışma grafı, Welch-Powell renklendirme ve dinamik güncelleme
└── ekran_goruntuleri/
    ├── soru1_cikti.png               # Soru 1 konsol çalışma ekran çıktısı
    ├── soru2_cikti.png               # Soru 2 konsol çalışma ekran çıktısı
    └── soru3_cikti.png               # Soru 3 konsol çalışma ekran çıktısı
```

---

## Soru 1: Ağ Güvenliği ve İki Parçalı Graf (Bipartite) Analizi

### Senaryo ve Problem Tanımı
Bir ağ yöneticisi, sunucular ve istemciler arasındaki bağlantıları iki farklı küme (İstemciler $U$ ve Sunucular $V$) arasında organize etmek istemektedir. Kendi kümesi içindeki cihazların birbirine doğrudan bağlanması güvenlik politikaları gereği yasaktır.

Verilen Kenar Kümesi:
$$E = \{(1, 2), (1, 4), (2, 3), (3, 4), (3, 6), (4, 5), (5, 6)\}, \quad |V| = 6, \quad |E| = 7$$

### 1. Komşuluk Matrisi ($6 \times 6$)
```text
     1  2  3  4  5  6 
   +------------------
 1 | 0  1  0  1  0  0 
 2 | 1  0  1  0  0  0 
 3 | 0  1  0  1  0  1 
 4 | 1  0  1  0  1  0 
 5 | 0  0  0  1  0  1 
 6 | 0  0  1  0  1  0 
```

### 2. Düğüm Dereceleri ve Grafın Genel Derecesi
* **Düğüm 1:** Derece = 2 (Komşular: 2, 4)
* **Düğüm 2:** Derece = 2 (Komşular: 1, 3)
* **Düğüm 3:** Derece = 3 (Komşular: 2, 4, 6)
* **Düğüm 4:** Derece = 3 (Komşular: 1, 3, 5)
* **Düğüm 5:** Derece = 2 (Komşular: 4, 6)
* **Düğüm 6:** Derece = 2 (Komşular: 3, 5)
* **Toplam Derece:** $2 \times |E| = 14$
* **Maksimum Derece ($\Delta(G)$):** 3 (Düğüm 3 ve Düğüm 4)
* **Ortalama Derece:** $14 / 6 \approx 2.33$

### 3. Bipartite Kontrolü (Renklendirme / Tek-Çift Yöntemi)
Başlangıç olarak 1 numaralı düğüme 0 (Mavi) rengi ve 0 uzaklığı atanır:
* **Düğüm 1:** Uzaklık = 0 (Çift) $\rightarrow$ Renk: 0 (Mavi) $\rightarrow$ **Küme U**
* **Düğüm 2:** Uzaklık = 1 (Tek) $\rightarrow$ Renk: 1 (Kırmızı) $\rightarrow$ **Küme V**
* **Düğüm 3:** Uzaklık = 2 (Çift) $\rightarrow$ Renk: 0 (Mavi) $\rightarrow$ **Küme U**
* **Düğüm 4:** Uzaklık = 1 (Tek) $\rightarrow$ Renk: 1 (Kırmızı) $\rightarrow$ **Küme V**
* **Düğüm 5:** Uzaklık = 2 (Çift) $\rightarrow$ Renk: 0 (Mavi) $\rightarrow$ **Küme U**
* **Düğüm 6:** Uzaklık = 3 (Tek) $\rightarrow$ Renk: 1 (Kırmızı) $\rightarrow$ **Küme V**

**Sonuç:** Graf **İKİ PARÇALIDIR (Bipartite)**.  
* $\text{Küme } U = \{1, 3, 5\}$
* $\text{Küme } V = \{2, 4, 6\}$  
Tüm kenarlar $U$ ile $V$ arasındadır. Aynı küme içinde hiçbir bağlantı yoktur, güvenlik kuralı sağlanır.

### 4. Dinamik Test: $(2, 4)$ Bağlantısı Eklendiğinde Ne Değişir?
* **Gözlem:** Graf **İKİ PARÇALI OLMAKTAN ÇIKAR (Not Bipartite)**!
* **Nedeni:** 
  1. Düğüm 2 ve Düğüm 4'ün her ikisi de **Küme V (Kırmızı / Tek parite)** elemanıdır.
  2. Aralarına $(2, 4)$ kenarı eklendiğinde aynı renge sahip iki komşu oluşur.
  3. Grafta $1 - 2 - 4 - 1$ şeklinde **3 kenarlı tek uzunluklu döngü (odd cycle / üçgen)** meydana gelir.
  4. Bir grafın iki parçalı olabilmesi için gerek ve yeter şart tek uzunluklu döngü içermemesidir.
  5. Ağ güvenliği açısından: Kendi kümesi içindeki iki istemci (2 ve 4) birbirine doğrudan bağlanarak güvenlik politikası ihlal edilmiştir.

#### Derleme ve Çalıştırma:
```bash
cd hafta11/cevaplar
gcc soru1.c -o soru1 && ./soru1
```

#### Ekran Görüntüsü:
![Soru 1 Çıktısı](ekran_goruntuleri/soru1_cikti.png)

---

## Soru 2: En Az Maliyetli Yol ve Merkezi Düğüm Analizi (Dijkstra)

### Senaryo ve Problem Tanımı
Bir lojistik firması, 6 dağıtım merkezi ($A, B, C, D, E, F$) arasındaki en kısa teslimat rotalarını ve ana aktarma merkezi (en merkezi düğüm) olarak seçilmesi gereken depoyu belirlemek istemektedir.

### Kenar ve Maliyet Listesi
* $A-B: 7, \quad A-C: 5, \quad A-F: 1$
* $B-C: 1, \quad B-D: 1, \quad B-E: 3$
* $C-D: 2, \quad C-E: 1$
* $D-F: 7, \quad E-F: 2$

### 1. Kök Düğüm A İçin Adım Adım Dijkstra Tablosu
| Adım | Seçilen Düğüm | Düğüm A | Düğüm B | Düğüm C | Düğüm D | Düğüm E | Düğüm F |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | **A** | **[0, -]** | [7, A] | [5, A] | [$\infty$, -] | [$\infty$, -] | [1, A] |
| 2 | **F** | [0, -] | [7, A] | [5, A] | [8, F] | [3, F] | **[1, A]** |
| 3 | **E** | [0, -] | [6, E] | [4, E] | [8, F] | **[3, F]** | [1, A] |
| 4 | **C** | [0, -] | [5, C] | **[4, E]** | [6, C] | [3, F] | [1, A] |
| 5 | **B** | [0, -] | **[5, C]** | [4, E] | [6, C] | [3, F] | [1, A] |
| 6 | **D** | [0, -] | [5, C] | [4, E] | **[6, C]** | [3, F] | [1, A] |

### 2. Kök Düğüm A İçin Rota Çıktıları
* **Hedef B:** $\mathbf{A \rightarrow F \rightarrow E \rightarrow C \rightarrow B}$ (Toplam Maliyet: **5**)
* **Hedef D:** $\mathbf{A \rightarrow F \rightarrow E \rightarrow C \rightarrow D}$ (Toplam Maliyet: **6**)

### 3. Merkezi Düğüm Tespiti (Closeness Centrality)
Algoritma her düğüm için çalıştırılarak diğer tüm düğümlere olan en kısa mesafeler toplamı hesaplanır:

| Düğüm | Mesafeler (A, B, C, D, E, F) | Toplam Ağ Maliyeti | Maksimum Mesafe (Eccentricity) |
| :---: | :--- | :---: | :---: |
| **A** | $0 + 5 + 4 + 6 + 3 + 1$ | **19** | 6 (D) |
| **B** | $5 + 0 + 1 + 1 + 2 + 4$ | **13** | 5 (A) |
| **C** | $4 + 1 + 0 + 2 + 1 + 3$ | **11** | 4 (A) |
| **D** | $6 + 1 + 2 + 0 + 3 + 5$ | **17** | 6 (A) |
| **E** | $3 + 2 + 1 + 3 + 0 + 2$ | **11** | 3 (A, D) |
| **F** | $1 + 4 + 3 + 5 + 2 + 0$ | **15** | 5 (D) |

**Sonuç ve Karar:**
* En düşük toplam ağ maliyetine sahip düğümler **C ve E** düğümleridir (Toplam Maliyet: **11**).
* Eksantriklik (maksimum erişim mesafesi) göz önüne alındığında, **E düğümü (Maks: 3)** en dengeli ve en merkezi dağıtım deposudur.

#### Derleme ve Çalıştırma:
```bash
cd hafta11/cevaplar
gcc soru2.c -o soru2 && ./soru2
```

#### Ekran Görüntüsü:
![Soru 2 Çıktısı](ekran_goruntuleri/soru2_cikti.png)

---

## Soru 3: Çakışmasız Sınav Takvimi (Welch-Powell Algoritması)

### Senaryo ve Problem Tanımı
6 farklı ders ($d_0, d_1, d_2, d_3, d_4, d_5$) için final sınav programı hazırlanacaktır. Aynı öğrencinin aldığı dersler çakışamaz.

* Öğrenci-1: $d_0, d_1, d_4$
* Öğrenci-2: $d_0, d_2, d_4$
* Öğrenci-3: $d_2, d_3, d_5$
* Öğrenci-4: $d_3, d_4, d_5$

### 1. Otomatik Çakışma Grafı Matrisi
```text
      d0  d1  d2  d3  d4  d5 
    +-------------------------
 d0 |  0   1   1   0   1   0 
 d1 |  1   0   0   0   1   0 
 d2 |  1   0   0   1   1   1 
 d3 |  0   0   1   0   1   1 
 d4 |  1   1   1   1   0   1 
 d5 |  0   0   1   1   1   0 
```

### 2. Welch-Powell Düğüm Dereceleri Sıralaması
1. **$d_4$:** Derece 5 (Tüm derslerle çakışır)
2. **$d_2$:** Derece 4
3. **$d_0, d_3, d_5$:** Derece 3
4. **$d_1$:** Derece 2

### 3. Sınav Oturumları Raporu (Orijinal Durum)
* **Kromatik Sayı ($\chi(G)$):** **4** (Grafta $\{d_2, d_3, d_4, d_5\}$ 4'lü klik ($K_4$) oluşturduğu için minimum 4 oturum zorunludur).
* **Oturum 1:** $\{d_4\}$
* **Oturum 2:** $\{d_2, d_1\}$
* **Oturum 3:** $\{d_3, d_0\}$
* **Oturum 4:** $\{d_5\}$

### 4. Dinamik Güncelleme Testi: Öğrenci-4 $d_4$ Dersini Bırakırsa
* **Senaryo:** Öğrenci-4 artık yalnızca $d_3$ ve $d_5$ almaktadır.
* **Kaldırılan Kenarlar:** $(d_3, d_4)$ ve $(d_4, d_5)$ bağlantıları silinir.
* **Gözlem:** $\{d_2, d_3, d_4, d_5\}$ arasındaki $K_4$ klik yapısı kırılır.
* **Güncel Kromatik Sayı:** **3'e DÜŞER** ($\chi(G') = 3$).
* **Güncel Oturum Dağılımı:**
  * **Oturum 1:** $\{d_2, d_1\}$
  * **Oturum 2:** $\{d_0, d_3\}$
  * **Oturum 3:** $\{d_4, d_5\}$
* **Kazanım:** Üniversite sınav programında 1 sınav oturumu tasarrufu sağlanmıştır.

#### Derleme ve Çalıştırma:
```bash
cd hafta11/cevaplar
gcc soru3.c -o soru3 && ./soru3
```

#### Ekran Görüntüsü:
![Soru 3 Çıktısı](ekran_goruntuleri/soru3_cikti.png)
