#include "hashtable.hpp"

using namespace std;

HashTable::HashTable(const int tSize): tableSize(tSize) {
    map = new AVL[tSize];
}

HashTable::~HashTable() {
    delete[] map;
}

int  HashTable::get_size() {
    return tableSize;
}

unsigned long long HashTable::hashFunction(Entry* e) {
    return e->get_hashvalue()%tableSize;
}

void HashTable::insert(Entry* e) {
    unsigned long long hashValue = hashFunction(e);
    // map[hashValue].print_preorder(map[hashValue].root);
    // std::cout << map[hashValue].get_size() << "\n";
    map[hashValue].root = map[hashValue].insert(map[hashValue].root, e);
}

Entry* HashTable::search(unsigned long long hash_value) {
    int bucket = hash_value%tableSize;
    return map[bucket].search(map[bucket].root, hash_value);
}