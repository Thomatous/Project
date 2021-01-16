#include "priority_list.hpp"

info::info(PriorityNode* n): address(n->address), ht_index(n->ht_index) {
    modified = n->modified;
}

PriorityNode::PriorityNode(const unsigned int pa, const unsigned int hi): address(pa), ht_index(hi) {
    modified = false;
    sc = false;
    next = prev = NULL;
}

PriorityNode::~PriorityNode() {

}

PriorityList::PriorityList() {
    size = 0;
    head = tail = victim = NULL;
}

PriorityList::~PriorityList() {
    PriorityNode* temp = head;
    while(temp != NULL) {
        PriorityNode* t = temp;
        temp = temp->next;
        delete t;
    }
}

PriorityNode* PriorityList::push(const unsigned int pa, const unsigned int ht_index) {
    PriorityNode* n = new PriorityNode(pa, ht_index);
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

info PriorityList::remove_from_end() {
    info i(tail);
    if( size == 1 ) {
        delete tail;
        head = tail = NULL;
        size = 0;
    } else {
        PriorityNode* temp = tail;
        tail->prev->next = NULL;
        tail = tail->prev;
        delete temp;
        size--;
    }

    return i;
}

void PriorityList::move_to_head(PriorityNode* node) {
    if(size > 1 && head != node) {
        if(node == tail) {
            tail->prev->next = NULL;
            tail = tail->prev;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        node->prev = NULL;
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void PriorityList::make_it_cycle() {
    tail->next = head;
    head->prev = tail;
    victim = tail;
}

info PriorityList::get_info(PriorityNode* pn) {
    info i(pn);
    return i;
}

PriorityNode* PriorityList::get_victim() {
    // find node to discard
    while( victim->sc ) {
        victim->sc = false;
        victim = victim->prev;
    }
    victim = victim->prev;

    return victim->next;
}

void PriorityList::replace(PriorityNode* pn, const unsigned int pa, const unsigned int hi, bool mod) {
    pn->address = pa;
    pn->sc = true;
    pn->ht_index = hi;
    pn->modified = mod;
}
