#ifndef _LIST_
#define _LIST_

#include <cstddef>
#include "record.hpp"

template <typename Type> 
class Node {
private:
    Type* item;
    Node* next;

public:
    Node<Type>(Type* i, Node* n=NULL){
        item = i;
        next = n;
    }

    ~Node<Type>() {
        // delete item;
        // std::cout << "Node deleted!" << std::endl;
    }

    Type* getItem() {
        return item;
    }

    void setNext(Node* n) {
        next = n;
    }

    Node* getNext() {
        return next;
    }
};

template <typename Type>
class List {
private:
    int size;
    Node<Type> *head;
    Node<Type> *tail;
    Node<Type> *toPop;

public:
    List<Type>() {
        size = 0;
        head = tail = toPop = NULL;
    }

    ~List<Type>() {
        Node<Type>* n = head;
        for(int i=0 ; i<size ; i++) {
            head = head->getNext();
            delete n;
            n = head;
        }
        // std::cout << "List deleted!" << std::endl;
    }

    List<Type>(Type* i){
        head = tail = toPop = new Node<Type>(i);
        size = 1;
    }

    void push(Type *value) {
        Node<Type> *p = new Node<Type>(value);
        if(head == NULL) {
            head = p;
            toPop = head;
        } else {
            tail->setNext(p);
        }
        tail = p;
        if(toPop == NULL) {
            toPop = tail;
        }
        size++;
    }

    // doesnt actually remove nodes from the list, just returns pointer to them
    // toPop pointer is used to mark till which point we have poped
    Type* pop() {
        if(toPop != NULL) {
            Type *p = toPop->getItem();
            toPop = toPop->getNext();
            return p;
        }
        return NULL;
    }

    void resetPop() {
        toPop = head;
    }

    record* searchRecord(std::string t) {
        Node<record> *n = head;
        while(n != NULL) {
            if(n->getItem()->getId()->compare(t) == 0) {
                return n->getItem();
            }
            n = n->getNext();
        }
        return NULL;
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        if(getSize()) {
            return false;
        }
        return true;
    }
    
};

#endif