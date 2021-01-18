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

    DoubleLinkedNode(Entry*, Entry*);
    ~DoubleLinkedNode();
};

struct DoubleLinkedList {
    unsigned int size;
    DoubleLinkedNode* head;
    DoubleLinkedNode* tail;

    DoubleLinkedList();
    ~DoubleLinkedList();
    DoubleLinkedNode* push(Entry*, Entry*);
    void pop_from_address(DoubleLinkedNode*);
    DoubleLinkedNode* pop();
};

#endif