#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <iostream>
#include "list.cpp"
#include <cstddef>
#include <cstring>
#include "avl.hpp"

////////////////////////////////////////////////////////////////

class Bucket {
private:
    int value;
    AVL* tree_p;
    Bucket* next;

public:
    Bucket(const int, Entry*);
    ~Bucket();
    int getValue();
    Bucket* getNext();
    void setValue(int);
    void setNext(Bucket*);
    AVL* getTree();
    int getNumPairs();
    void increaseNumPairs();
};

////////////////////////////////////////////////////////////////

class HashTable {
private:
    const int tableSize;
    Bucket* head;

public:
    HashTable(const int);
    ~HashTable();
    int hashFunction(Entry*);
    bool isEmpty();
    Bucket* findBucket(const int);
    void insert(Entry*);
};

#endif