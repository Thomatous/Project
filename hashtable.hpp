#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <iostream>
// #include "list.cpp"
#include <cstddef>
#include <cstring>
#include "avl.hpp"

class HashTable {
private:
    const int tableSize;
    AVL* map;

public:
    HashTable(const int);
    ~HashTable();
    int get_size();
    unsigned long long hashFunction(Entry*);
    void insert(Entry*);
    Entry* search(unsigned long long); // search the right tree based on entry hashvalue
};

#endif