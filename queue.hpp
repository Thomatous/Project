#ifndef _QUEUE_
#define _QUEUE_

#include <stdio.h>
#include "job_scheduler.hpp"

class Job;
struct QueueNode {
    Job* job;
    QueueNode* next;

    QueueNode(Job*);
    ~QueueNode();
};

struct Queue {
    QueueNode* head;
    QueueNode* tail;
    unsigned int size;

    Queue();
    ~Queue();
    void push_back(Job*);
    Job* pop();
};
#endif