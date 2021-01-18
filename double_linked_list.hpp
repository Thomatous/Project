#ifndef _DoubleLinked_LIST_
#define _DoubleLinked_LIST_

#include <iostream>
#include "entry.hpp"


struct DoubleLinkedNode {
    Entry* A;
    Entry* B;
    float pred;
    DoubleLinkedNode* next;
    DoubleLinkedNode* prev;
    DoubleLinkedNode();
    DoubleLinkedNode(Entry*, Entry*, float);
    ~DoubleLinkedNode();
};

struct DoubleLinkedList {
    unsigned int size;
    DoubleLinkedNode* head;
    DoubleLinkedNode* tail;

    DoubleLinkedList();
    ~DoubleLinkedList();
    DoubleLinkedNode* push(Entry*, Entry*, float);
    void pop_from_address(DoubleLinkedNode*);
};

#endif