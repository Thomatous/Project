#include "queue.hpp"

QueueNode::QueueNode(Job* j) {
    job = j;
    next = NULL;
}

QueueNode::~QueueNode() {
    job = NULL;
    next = NULL;
}

Queue::Queue() {
    size = 0;
    head = tail = NULL;
}

Queue::~Queue() {
    while( size > 0) {
        this->pop();
    }
}

void Queue::push_back(Job* j) {
    if( size == 0 ) {
        head = tail = new QueueNode(j);
    } else {
        tail->next = new QueueNode(j);
        tail = tail->next;
    }
    ++size;
}

Job* Queue::pop() {
    QueueNode* temp = head;
    if( size == 1 ) {
        head = tail = NULL;
    } else {
        head = head->next;
    }
    --size;
    Job* j = temp->job;
    delete temp; 

    return j;
}