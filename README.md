# 📞 Telefon Rehberi Uygulamasında  
## Sıralama ve Arama Algoritmalarının Performans Analizi

Bu proje, bir **telefon rehberi veri seti** üzerinde farklı **sıralama** ve **arama algoritmalarının** performanslarını karşılaştırmalı olarak incelemek amacıyla geliştirilmiştir.  
Uygulama **C++** programlama dili ile yazılmış, algoritmaların çalışma süreleri **nanosecond (ns)** hassasiyetinde ölçülmüş ve sonuçlar analiz edilmiştir.

---

## 🎯 Projenin Amacı

- Farklı **veri boyutlarında** algoritmaların davranışını gözlemlemek  
- Arama ve sıralama algoritmaları arasındaki **performans farklarını** ortaya koymak  
- **Teorik zaman karmaşıklığı** ile **pratik sonuçları** karşılaştırmak  

---

## 🗂️ Kullanılan Veri Yapısı

Veriler, her satırı aşağıdaki formatta olan metin dosyalarından okunur:


Her kayıt `Contact` adlı yapı (`struct`) ile temsil edilir:

- `fullName` → Kişinin adı (büyük harfe çevrilir)
- `phone` → Telefon numarası
- `city` → Şehir bilgisi

---

## ⚙️ Kullanılan Algoritmalar

### 🔢 Sıralama Algoritmaları

Aynı veri setinin kopyaları üzerinde aşağıdaki algoritmalar uygulanmıştır:

| Algoritma        | Açıklama                                                   | Zaman Karmaşıklığı |
|------------------|------------------------------------------------------------|--------------------|
| Insertion Sort   | Küçük veri setleri için uygundur                           | O(n²)              |
| Quick Sort       | Median-of-three pivot, küçük dizilerde insertion sort      | Ortalama O(n log n)|
| Merge Sort       | In-place birleştirme kullanır                              | O(n log n)         |
| Heap Sort        | Binary heap yapısı                                         | O(n log n)         |

---

### 🔍 Arama Algoritmaları

| Algoritma           | Özellik                                                     | Zaman Karmaşıklığı |
|---------------------|-------------------------------------------------------------|--------------------|
| Sequential Search   | Tüm dizi taranır, prefix eşleşmesi desteklenir              | O(n)               |
| Binary Search       | Sıralı veri üzerinde çalışır, prefix için genişleme yapar  | O(log n)           |

---

## ⏱️ Zaman Ölçümü

- Zaman ölçümleri `std::chrono::high_resolution_clock` kullanılarak yapılmıştır.
- **Sıralama algoritmaları** tek sefer çalıştırılmıştır.
- **Arama algoritmaları**, daha hassas ölçüm için **1000 kez çalıştırılıp ortalama süre alınmıştır**.
- Tüm süreler **nanosecond (ns)** cinsindendir.

---

## 📊 Deneysel Sonuçlar (Özet)

### Küçük Veri Setleri
- Sıralama süreleri birbirine oldukça yakındır.
- Binary Search, Sequential Search’ten daha hızlıdır.
- SpeedUp oranları düşük ancak anlamlıdır.

### Orta Boy Veri Setleri
- Insertion Sort belirgin şekilde yavaşlamıştır.
- Quick Sort en hızlı sıralama algoritması olmuştur.
- Binary Search ≈ **3.6 kat** daha hızlıdır.

### Büyük Veri Setleri
- Insertion Sort ciddi performans kaybı yaşamıştır.
- Quick Sort ve Heap Sort ölçeklenebilir sonuçlar vermiştir.
- Binary Search, Sequential Search’e göre **100+ kat** daha hızlı çalışmıştır.

---

## 🚀 SpeedUp Analizi

### Arama Algoritmaları


- Küçük veri setleri: **2–7 kat**
- Büyük veri setleri: **100+ kat**

### Sıralama Algoritmaları  
(Referans: Quick Sort)

- Insertion Sort → Büyük veri setlerinde çok yavaş  
- Merge Sort → Daha stabil ama daha yavaş  
- Heap Sort → Quick Sort’a yakın performans  

---

## 🧠 Sonuç

- **Quick Sort**, genel olarak en dengeli ve hızlı sıralama algoritmasıdır.
- **Insertion Sort**, yalnızca çok küçük veri setleri için uygundur.
- **Binary Search**, sıralı veri üzerinde arama performansını dramatik biçimde artırır.
- Büyük veri setlerinde **algoritma seçimi**, uygulama performansını doğrudan etkilemektedir.

Bu proje, **asemptotik karmaşıklığın gerçek dünya uygulamalarındaki etkisini** açıkça göstermektedir.

---

## 🛠️ Derleme ve Çalıştırma

```bash
g++ -std=c++11 main.cpp -o phonebook
./phonebook
