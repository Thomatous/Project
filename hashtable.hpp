#ifndef _HASHTABLE_
#define _HASHTABLE_

#define A 719 // prime number
#define B 277 // prime number

#define INF "99-99-9999"
#define NINF "00-00-00"

#define COUNTRY "country"
#define DISEASE "disease"

#include <iostream>
#include "list.cpp"
#include <cstddef>
#include <cstring>
#include "tree.hpp"
#include "max_heap.hpp"


class Pair {
public:
    std::string *data;
    avlTree* tree;
    Pair* next;

    Pair(std::string*, record*);
    ~Pair();
};

////////////////////////////////////////////////////////////////

class Bucket {
private:
    int value;
    Pair *keys;
    int numOfPairs;
    Bucket* next;

public:
    Bucket(const int, std::string, record*);
    ~Bucket();
    int getValue();
    Bucket* getNext();
    void setValue(int);
    void setNext(Bucket*);
    avlTree* getTree();
    Pair* getKeys();
    Pair* search(Pair*, std::string, record*);
    int getNumPairs();
    void increaseNumPairs();
};

////////////////////////////////////////////////////////////////

class HashTable {
private:
    int tableSize;
    int bucketSize;
    Bucket* head;

public:
    HashTable(const int, const int);
    ~HashTable();
    int hashFunction(const std::string);
    bool isEmpty();
    Bucket* findBucket(const std::string);
    void insert(std::string, record*);
    void numCurrentPatients(std::string);
    void numCurrentPatients();
    void globalDiseaseStats(std::string, std::string);
    void globalDiseaseStats();
    void diseaseFrequency(std::string, std::string, std::string, std::string);
    void diseaseFrequency(std::string, std::string, std::string);
    void topk(List<HeapPair>*, std::string, std::string);
    void topk(List<HeapPair>*, std::string, std::string, std::string, std::string);
};

#endif