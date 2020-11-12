#include "hashtable.hpp"

using namespace std;

// creating bucket based on its first entry
Bucket::Bucket(const int val, Entry* e) {
    next = NULL;
    value = val;
    tree_p = new AVL();
    tree_p->root = tree_p->insert(tree_p->root, e); //
    // std::cout << "Bucket " << value << " created!" << std::endl;
}

Bucket::~Bucket() {
    // std::cout << "Bucket Destroyed!" << std::endl;
}

int Bucket::getValue() {
    return value;
}

Bucket* Bucket::getNext() {
    return next;
}

void Bucket::setValue(int val) {
    value = val;
}

void Bucket::setNext(Bucket* hnp) {
    next = hnp;
}

AVL* Bucket::getTree() {
    return tree_p;
}

/////////////////////////////////////////////////////////////////////////

HashTable::HashTable(const int tSize): tableSize(tSize) {
    map = new AVL[tSize];
}

HashTable::~HashTable() {
    delete[] map;
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
