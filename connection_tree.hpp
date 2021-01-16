#ifndef _ConnectionTree_
#define _ConnectionTree_

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "entry.hpp"  

class Entry;
class ConnectionNode{
    private:
        unsigned int height;
        Entry* data;
    public:
        ConnectionNode* left;
        ConnectionNode* right;

        ConnectionNode();
        ConnectionNode(Entry*);
        ~ConnectionNode();
        void set_height(int);
        void set_vector_loc(unsigned int);
        unsigned int get_height();
        Entry* get_data();
        void update_height();
        int get_vector_loc();
};

class ConnectionTree{
    private:
        unsigned int size;
    public:
        ConnectionNode* root;
        
        ConnectionTree();
        ~ConnectionTree();
        void clear(ConnectionNode*);
        unsigned int get_size();
        int get_balance(ConnectionNode*);
        ConnectionNode* right_rotate(ConnectionNode*);
        ConnectionNode* left_rotate(ConnectionNode*);
        ConnectionNode* insert(ConnectionNode*, Entry*);
        bool find(ConnectionNode*, Entry*);
};
#endif