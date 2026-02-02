#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;

// Veri Yapısı
struct Contact {
    string fullName; 
    string phone;
    string city;

    // Sıralama ve arama için operatörler
    bool operator<(const Contact& other) const {
        return fullName < other.fullName;
    }
    bool operator>(const Contact& other) const {
        return fullName > other.fullName;
    }
    bool operator<=(const Contact& other) const {
        return fullName <= other.fullName;
    }
};

// Fonksiyonlar
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

bool startsWith(const string& text, const string& prefix) {
    if (prefix.length() > text.length()) return false;
    return text.substr(0, prefix.length()) == prefix;
}

// Dosya Okuma
vector<Contact> loadPhoneBook(const string& filename) {
    vector<Contact> contacts;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Dosya acilamadi: " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string segment;
        vector<string> parts;
        
        while(getline(ss, segment, ' ')) {
            if(!segment.empty()) parts.push_back(segment);
        }

        if (parts.size() >= 3) {
            Contact c;
            c.city = parts.back(); 
            c.phone = parts[parts.size() - 2]; 
            
            string nameStr = "";
            for (size_t i = 0; i < parts.size() - 2; ++i) {
                nameStr += parts[i] + (i == parts.size() - 3 ? "" : " ");
            }
            c.fullName = toUpper(nameStr); 
            contacts.push_back(c);
        }
    }
    file.close();
    return contacts;
}

// SIRALAMA ALGORİTMALARI 

// Insertion Sort
void insertionSort(vector<Contact>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        Contact key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void insertionSortWrapper(vector<Contact>& arr) {
    insertionSort(arr, 0, arr.size() - 1);
}

// Quick Sort
int medianOfThree(vector<Contact>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low]) swap(arr[low], arr[mid]);
    if (arr[high] < arr[low]) swap(arr[low], arr[high]);
    if (arr[high] < arr[mid]) swap(arr[mid], arr[high]);
    return mid; 
}

int partition(vector<Contact>& arr, int low, int high) {
    int pivotIndex = medianOfThree(arr, low, high);
    swap(arr[pivotIndex], arr[high]); // Pivotu sona al
    Contact pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<Contact>& arr, int low, int high) {
    while (low < high) {
        if (high - low < 10) {
            insertionSort(arr, low, high);
            break;
        } else {
            int pi = partition(arr, low, high);
            
            if (pi - low < high - pi) {
                quickSort(arr, low, pi - 1);
                low = pi + 1;
            } else {
                quickSort(arr, pi + 1, high);
                high = pi - 1;
            }
        }
    }
}

void quickSortWrapper(vector<Contact>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// Merge Sort
void mergeInPlace(vector<Contact>& arr, int start, int mid, int end) {
    int start2 = mid + 1;

    if (arr[mid] <= arr[start2]) {
        return;
    }

    while (start <= mid && start2 <= end) {
        if (arr[start] <= arr[start2]) {
            start++;
        } else {
            Contact value = arr[start2];
            int index = start2;

            while (index != start) {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[start] = value;

            start++;
            mid++;
            start2++;
        }
    }
}

void mergeSort(vector<Contact>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        mergeInPlace(arr, l, m, r);
    }
}

void mergeSortWrapper(vector<Contact>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

// Heap Sort
void heapify(vector<Contact>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSortWrapper(vector<Contact>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ARAMA ALGORİTMALARI

// Linear Search
vector<Contact> sequentialSearch(const vector<Contact>& arr, const string& query) {
    vector<Contact> results;
    string uQuery = toUpper(query);
    for (const auto& contact : arr) {
        // İsim tam eşleşiyor mu VEYA kısmi başlangıç (prefix) eşleşiyor mu?
        if (startsWith(contact.fullName, uQuery)) {
            results.push_back(contact);
        }
    }
    return results;
}

// Binary Search
vector<Contact> binarySearch(const vector<Contact>& arr, const string& query) {
    vector<Contact> results;
    string uQuery = toUpper(query);
    int left = 0, right = arr.size() - 1;
    int foundIndex = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (startsWith(arr[mid].fullName, uQuery)) {
            foundIndex = mid;

            break; 
        }
        
        if (arr[mid].fullName < uQuery)
            left = mid + 1;
        else
            right = mid - 1;
    }

    if (foundIndex != -1) {
        int temp = foundIndex;
        while (temp >= 0 && startsWith(arr[temp].fullName, uQuery)) {
            temp--;
        }
        int startRange = temp + 1;

        temp = foundIndex;
        while (temp < arr.size() && startsWith(arr[temp].fullName, uQuery)) {
            temp++;
        }
        int endRange = temp - 1;

        for (int i = startRange; i <= endRange; ++i) {
            results.push_back(arr[i]);
        }
    }

    return results;
}

// Zaman Ölçümü
template <typename Func>
double measureTime(Func func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double, nano>(end - start).count();
}

int main() {
    string filename, query;
    cout << "Lutfen iletisim dosyasinin adini girin: " << endl;
    cin >> filename;
    
    // Temizleme
    cin.ignore(); 

    cout << "Lutfen sorgulanacak kelimeyi girin: " << endl;
    getline(cin, query);

    // Dosyayı oku
    vector<Contact> data = loadPhoneBook(filename);
    if (data.empty()) {
        cout << "Rehber bos veya hatali format!" << endl;
        return 0;
    }

    // Vektör kopyalarını oluştur
    vector<Contact> vQuick = data;
    vector<Contact> vInsertion = data;
    vector<Contact> vMerge = data;
    vector<Contact> vHeap = data;

    cout << "\nVektor kopyalarini siralama" << endl;
    cout << "======================================" << endl;

    // SIRALAMA SÜRELERİNİ ÖLÇME
    
    double tQuick = measureTime([&]() { quickSortWrapper(vQuick); });
    cout << "Quick Sort Zamani: " << (long long)tQuick << " Nanoseconds" << endl;

    double tInsertion = measureTime([&]() { insertionSortWrapper(vInsertion); });
    cout << "Insertion Sort Zamani: " << (long long)tInsertion << " Nanoseconds" << endl;

    double tMerge = measureTime([&]() { mergeSortWrapper(vMerge); });
    cout << "Merge Sort Zamani: " << (long long)tMerge << " Nanoseconds" << endl;

    double tHeap = measureTime([&]() { heapSortWrapper(vHeap); });
    cout << "Heap Sort Zamani: " << (long long)tHeap << " Nanoseconds" << endl;

    // ARAMA SÜRELERİNİ ÖLÇME VE SONUÇLAR
    
    cout << "\n'" << query << "' icin Arama" << endl;
    cout << "======================================" << endl;

    // Binary Search
    // Daha Hassas bir ölçüm için N kez çalıştırıp ortalamasını alacağız.
    int iterations = 1000;
    double totalBinary = 0;
    vector<Contact> resBinary;
    
    for(int i=0; i<iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        resBinary = binarySearch(vQuick, query); // Arama sonucu değişmez
        auto end = chrono::high_resolution_clock::now();
        totalBinary += chrono::duration<double, nano>(end - start).count();
    }
    double tBinary = totalBinary / iterations;

    
    if (resBinary.empty()) {
        cout << toUpper(query) << " veri setinde mevcut degildir." << endl;
    } else {

    }
    cout << "Binary Search Zamani: " << tBinary << " Nanoseconds" << endl;

    // Sequential Search
    double totalSeq = 0;
    vector<Contact> resSeq;
    for(int i=0; i<iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        resSeq = sequentialSearch(vQuick, query); 
        auto end = chrono::high_resolution_clock::now();
        totalSeq += chrono::duration<double, nano>(end - start).count();
    }
    double tSeq = totalSeq / iterations;

    cout << "Sequential Search icin Arama Sonuclari:" << endl;
    if (resSeq.empty()) {
        cout << toUpper(query) << " veri setinde mevcut degildir." << endl;
    } else {
        for (const auto& c : resSeq) {
            cout << c.fullName << " " << c.phone << " " << c.city << endl;
        }
    }
    cout << "Sequential Search Zamani: " << tSeq << " Nanoseconds" << endl;


    // SPEEDUP HESAPLAMALARI 

    cout << "\nArama Algoritmalari Arasinda Hizlanma Orani" << endl;
    cout << "======================================" << endl;
    cout << "(Sequential Search / Binary Search) SpeedUp = " << (tSeq / tBinary) << endl;

    cout << "\nSiralama Algoritmalari Arasinda Hizlanma Orani" << endl;
    cout << "======================================" << endl;
    
    cout << "(Insertion Sort / Quick Sort) SpeedUp = " << (tInsertion / tQuick) << endl;
    cout << "(Merge Sort / Quick Sort) SpeedUp = " << (tMerge / tQuick) << endl;
    cout << "(Heap Sort / Quick Sort) SpeedUp = " << (tHeap / tQuick) << endl;

    return 0;
}