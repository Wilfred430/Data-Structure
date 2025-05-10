template <typename K, typename V>
class MyHashTable {
private:
    struct Entry {
        K key;
        V value;
        bool occupied;
        Entry() : occupied(false) {}
    };

    Entry* table;
    int capacity;

    // 自定義 hash 函數
    int hash(const K& key) {
        return std::abs(static_cast<int>(key)) % capacity;
    }

public:
    MyHashTable(int size = 1000) {
        capacity = getPrime(size);
        table = new Entry[capacity];
    }

    ~MyHashTable() {
        delete[] table;
    }

    void insert(const K& key, const V& value) {
        int index = hash(key);
        int i = 0;
        while (i < capacity && table[(index + i) % capacity].occupied) {
            if (table[(index + i) % capacity].key == key)
                break;
            i++;
        }
        if (!table[(index + i) % capacity].occupied) {
            table[(index + i) % capacity].key = key;
        }
        table[(index + i) % capacity].value = value;
        table[(index + i) % capacity].occupied = true;
    }

    bool find(const K& key, V& value) {
        int index = hash(key);
        int i = 0;
        while (i < capacity) {
            int pos = (index + i) % capacity;
            if (!table[pos].occupied)
                return false;
            if (table[pos].key == key) {
                value = table[pos].value;
                return true;
            }
            i++;
        }
        return false;
    }

    // 找質數作為容量大小（減少碰撞）
    int getPrime(int n) {
        n++;
        while (true) {
            bool is_prime = true;
            for (int i = 2; i*i <= n; ++i) {
                if (n % i == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) return n;
            n++;
        }
    }
};

#include <iostream>
#include <fstream>
#include <vector>

// 假設你已經實作了 MyHashTable<K, V>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./Lab4 <input_file> <output_file>\n";
        return 1;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    long long target;
    fin >> target;

    std::vector<int> nums;
    int num;
    while (fin >> num) {
        nums.push_back(num);
    }

    MyHashTable<long long, int> hashTable(nums.size());

    for (int i = 0; i < nums.size(); ++i) {
        long long a = nums[i];
        if (a == 0) {
            if (target == 0) {
                // 處理 target == 0 的情況
                fout << "0 " << i << "\n";
                return 0;
            }
            continue;
        }

        if (target % a != 0) continue;

        long long b = target / a;
        int index_b;
        if (hashTable.find(b, index_b)) {
            fout << index_b << " " << i << "\n";
            return 0;
        }

        hashTable.insert(a, i);
    }

    // 沒找到
    fout << "-1 -1\n";
    return 0;
}