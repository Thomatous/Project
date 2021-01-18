#include "double_linked_list.hpp"


DoubleLinkedNode::DoubleLinkedNode(Entry* a, Entry* b){
    A = a;
    B = b;
    pred = -1;
    next = prev = NULL;
}

DoubleLinkedNode::~DoubleLinkedNode() {

}

DoubleLinkedList::DoubleLinkedList() {
    size = 0;
    head = tail = NULL;
}

DoubleLinkedList::~DoubleLinkedList() {
    DoubleLinkedNode* temp = head;
    while(temp != NULL) {
        DoubleLinkedNode* t = temp;
        temp = temp->next;
        delete t;
    }
}

DoubleLinkedNode* DoubleLinkedList::push(Entry* a, Entry* b) {
    DoubleLinkedNode* n = new DoubleLinkedNode(a, b);
    if( size == 0 ) {
        head = tail = n;
    } else {
        n->next = head;
        head->prev = n;
        head = n;
    }
    size++;

    return n;
}

void DoubleLinkedList::pop_from_address(DoubleLinkedNode* node) {
    if(size > 1 && head != node) {
        if(node == tail) {
            tail->prev->next = NULL;
            tail = tail->prev;
        } 
        else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }
    else{
        head = tail = NULL;
    }
    size--;
    delete node;
}

DoubleLinkedNode* DoubleLinkedList::pop() {
    DoubleLinkedNode* temp = head;
    if( size > 1 ) {
        head = head->next;
    } else {
        head = tail = NULL;
    }
    size--;
}