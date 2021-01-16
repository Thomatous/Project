#ifndef _PRIORITY_LIST_
#define _PRIORITY_LIST_

#include <iostream>

#define PAGE_SIZE 4096

struct PriorityNode {
    unsigned int address;
    unsigned int ht_index;
    bool modified;
    bool sc;
    PriorityNode* next;
    PriorityNode* prev;

    PriorityNode(const unsigned int, const unsigned int);
    ~PriorityNode();
};

struct info {
    const unsigned int address;
    const unsigned int ht_index;
    bool modified;

    info(PriorityNode*);
};

struct PriorityList {
    unsigned int size;
    PriorityNode* head;
    PriorityNode* tail;
    PriorityNode* victim;

    PriorityList();
    ~PriorityList();
    PriorityNode* push(const unsigned int, const unsigned int);
    info remove_from_end();
    void move_to_head(PriorityNode*);
    void make_it_cycle();
    info get_info(PriorityNode*);
    PriorityNode* get_victim();
    void replace(PriorityNode*, const unsigned int, const unsigned int, bool);
};

#endif