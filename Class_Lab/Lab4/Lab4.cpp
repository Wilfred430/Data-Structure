#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Hash table implementation using templates
template <typename KeyType, typename ValueType>
class HashTable {
private:
    // Node structure for chaining
    struct Node {
        KeyType key;
        ValueType value;
        Node* next;
        
        Node(KeyType k, ValueType v) : key(k), value(v), next(nullptr) {}
    };
    
    static const int DEFAULT_SIZE = 10000000; // Prime number for better distribution
    vector<Node*> table;
    int size;
    
    // Hash function for integers
    int hashFunction(const KeyType& key) const {
        return abs(static_cast<int>(key)) % size;
    }
    
public:
    HashTable(int tableSize = DEFAULT_SIZE) : size(tableSize) {
        table.resize(size, nullptr);
    }
    
    ~HashTable() {
        // Clean up all nodes
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    
    // Insert a key-value pair
    void insert(const KeyType& key, const ValueType& value) {
        int index = hashFunction(key);
        
        // Check if key already exists
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value; // Update existing value
                return;
            }
            current = current->next;
        }
        
        // Key doesn't exist, add a new node at the beginning of the chain
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }
    
    // Find value associated with key
    // Returns true if key is found, false otherwise
    // Value is returned through the reference parameter
    bool find(const KeyType& key, ValueType& value) const {
        int index = hashFunction(key);
        
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        
        return false; // Key not found
    }
    
    // Check if key exists in the table
    bool contains(const KeyType& key) const {
        int index = hashFunction(key);
        
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        
        return false;
    }
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./Lab4 <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }

    if (!fout.is_open()) {
        cerr << "Error opening output file: " << argv[2] << endl;
        return 1;
    }

    // Read target number
    long long target;
    fin >> target;
    fin.ignore(); // Skip the newline

    // Read array of numbers
    string line;
    getline(fin, line);
    stringstream ss(line);
    
    vector<int> numbers;
    int num;
    while (ss >> num) {
        numbers.push_back(num);
    }
    
    // Create hash table
    HashTable<int, int> hashTable;
    
    // Store numbers in hash table with their indices
    for (int i = 0; i < numbers.size(); i++) {
        hashTable.insert(numbers[i], i);
    }
    
    // Find two numbers whose product is equal to target
    pair<int, int> solution = {-1, -1};
    
    for (int i = 0; i < numbers.size(); i++) {
        // Skip if current number is 0 and target is not 0
        if (numbers[i] == 0 && target != 0) continue;
        
        // To avoid division by zero
        if (numbers[i] == 0) {
            if (target == 0) {
                // Look for another 0 in the hash table
                for (int j = i + 1; j < numbers.size(); j++) {
                    if (numbers[j] == 0) {
                        // Found a solution: two zeros
                        if (solution.first == -1 || (i < solution.first || 
                            (i == solution.first && j < solution.second))) {
                            solution = {i, j};
                        }
                        break;
                    }
                }
            }
            continue;
        }
        
        // Check if target is divisible by numbers[i]
        if (target % numbers[i] != 0) continue;
        
        // Calculate the complementary number
        int complement = target / numbers[i];
        
        // Find the complement in the hash table
        int complementIndex;
        if (hashTable.find(complement, complementIndex)) {
            // Avoid using the same index twice
            if (i != complementIndex) {
                // Check if this is the first solution or if it has smaller indices
                if (solution.first == -1 || 
                    (min(i, complementIndex) < min(solution.first, solution.second)) ||
                    (min(i, complementIndex) == min(solution.first, solution.second) && 
                     max(i, complementIndex) < max(solution.first, solution.second))) {
                    solution = {min(i, complementIndex), max(i, complementIndex)};
                }
            }
        }
    }
    
    // Write the result to the output file
    fout << solution.first << " " << solution.second << endl;
    
    fin.close();
    fout.close();
    
    return 0;
}