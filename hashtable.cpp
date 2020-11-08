#include "hashtable.hpp"

using namespace std;

// creating bucket based on its first entry
Bucket::Bucket(const int val, Entry* e) {
    next = NULL;
    value = val;
    tree_p = new AVL();
    tree_p->insert(e); //
    // std::cout << "Bucket " << value << " created!" << std::endl;
}

Bucket::~Bucket() {
    // std::cout << "Bucket Destroyed!" << std::endl;
}

int Bucket::getValue() {
    return value;
}

Bucket* Bucket::getNext() {
    return next;
}

void Bucket::setValue(int val) {
    value = val;
}

void Bucket::setNext(Bucket* hnp) {
    next = hnp;
}

AVL* Bucket::getTree() {
    return tree_p;
}

/////////////////////////////////////////////////////////////////////////

HashTable::HashTable(const int tSize): tableSize(tSize), head(NULL) {
}

HashTable::~HashTable() {
    Bucket* b = head;
    while(b != NULL) {
        head = head->getNext();
        delete b;
        b = head;
    }
    // cout << "Hashtable deleted!" << endl;
}

int HashTable::hashFunction(Entry* e) {
    std::string site = e->get_page_title();
    std::string id = e->get_id();
    unsigned long long hashValue = 5381;

    int c;
    const char* site_c = site.c_str();
    const char* id_c = id.c_str();

    while (c = *site_c++)
        hashValue = ((hashValue << 5) + hashValue) + c; /* hash * 33 + c */

    while (c = *id_c++)
        hashValue = ((hashValue << 5) + hashValue) + c; /* hash * 33 + c */

    return hashValue%tableSize;
}

bool HashTable::isEmpty() {
    if(!head) {
        return true;
    }
    return false;
}

// // returns possible bucket of given string
Bucket* HashTable::findBucket(const int val) {
    Bucket* temp;
    temp = head;
    while(temp) {
        if (temp->getValue() == val) {
            return temp;
        }
        temp = temp->getNext();
    }
    return NULL;
}

void HashTable::insert(Entry* e) {
    int hashValue = hashFunction(e);
    if (head == NULL) {
        head = new Bucket(hashValue, e);
    } else { //head exists
        // get bucket if exists else null
        Bucket* b = findBucket(hashValue);
        if (b != NULL) { // insert entry in its avl tree
            b->getTree()->insert(e);
        } else { // create new bucket
            Bucket* temp;
            temp = head;
            while(temp->getNext()) {
                temp = temp->getNext();
            }

            temp->setNext(new Bucket(hashValue, e));
        }
    }
}
