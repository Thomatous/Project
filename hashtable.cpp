#include "hashtable.hpp"

using namespace std;

Pair::Pair(string* sdata, record* r) {
    data = sdata;
    tree = new avlTree();
    tree->root = tree->insert(tree->root, r);
    next = NULL;
}

Pair::~Pair() {
    delete tree;
    // cout << "Pair destroyed!" << endl;
}

/////////////////////////////////////////////////////////////////////

// creating bucket based on its first entry
Bucket::Bucket(const int val, string s, record* r) {
    next = NULL;
    value = val;
    std::string *sdata;
    if( s.compare(DISEASE) == 0 ) {
        sdata = r->getDisease();
    } else if( s.compare(COUNTRY) == 0 ) {
        sdata = r->getCountry();
    }
    keys = new Pair(sdata, r);
    numOfPairs = 1;
    // std::cout << "Bucket " << value << " created!" << std::endl;
}

Bucket::~Bucket() {
    Pair* p = keys;
    while(p != NULL) {
        keys = keys->next;
        delete p;
        p = keys;
    }
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

avlTree* Bucket::getTree() {
    return keys->tree;
}

Pair* Bucket::getKeys() {
    return keys;
}

// if given country/disease (from record) is same with a pair's data return this pair
Pair* Bucket::search(Pair* head, string hashType, record* r) {
    Pair* temp = head;
    std::string s; 
    while(temp != NULL) {
        s = *temp->data;
        if ( s.compare(*r->getRecordField(hashType)) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int Bucket::getNumPairs() {
    return numOfPairs;
}

void Bucket::increaseNumPairs() {
    numOfPairs++;
}

/////////////////////////////////////////////////////////////////////////

HashTable::HashTable(const int tSize, const int bSize): tableSize(tSize),bucketSize(bSize), head(NULL) {
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

int HashTable::hashFunction(const std::string s) {
    unsigned long long hashValue = A;
    for(int i=0 ; i<s.length() ; i++) {
        hashValue = ((hashValue << 5) + hashValue) + s[i];
    }
    return hashValue%tableSize;
}

bool HashTable::isEmpty() {
    if(!head) {
        return true;
    }
    return false;
}

// returns possible bucket of given string
Bucket* HashTable::findBucket(const std::string s) {
    Bucket* temp;
    int val = hashFunction(s);
    temp = head;
    while(temp) {
        if (temp->getValue() == val) {
            return temp;
        }
        temp = temp->getNext();
    }
    return NULL;
}

void HashTable::insert(string hashType, record* r) {
    int hashValue = hashFunction(*r->getRecordField(hashType));
    if(head == NULL) {
        head = new Bucket(hashValue, hashType, r);
    } else {
        // get bucket if exists else null
        Bucket* b = findBucket(*r->getRecordField(hashType));
        // find right pair if exists else create one
        if(b != NULL) {
            int val = b->getValue();
            Pair* p = NULL;
            while(true) {
                p = b->search(b->getKeys(), hashType, r);
                if(p != NULL) {
                    break;
                }
                if(b->getNext() != NULL && b->getNext()->getValue() == val) {
                    b = b->getNext();
                } else {
                    break;
                }
            }
            if(p != NULL) { //insert at pair
                p->tree->root = p->tree->insert(p->tree->root, r);
            } else { //create new pair
                int spaceTaken = 2*sizeof(int) + sizeof(Bucket*) + (b->getNumPairs())*sizeof(Pair);
                // if there is space in this bucket create it here
                if(bucketSize - spaceTaken >= sizeof(Pair)) {
                    Pair* temp = b->getKeys();
                    while(temp->next != NULL) {
                        temp = temp->next;
                    }
                    temp->next = new Pair(r->getRecordField(hashType), r);
                    b->increaseNumPairs();
                } else { // create new bucket with same hashvalue and create it there 
                    Bucket* btmp = b->getNext();
                    Bucket* nb = new Bucket(hashValue, hashType, r);
                    nb->setNext(btmp);
                    b->setNext(nb);
                    if(b == NULL){}
                }
            }
        } else { // create new bucket
            Bucket* temp;
            temp = head;
            while(temp->getNext()) {
                temp = temp->getNext();
            }

            temp->setNext(new Bucket(hashValue, hashType, r));
        }
    }
}

void HashTable::numCurrentPatients(std::string disease) {
    int val = hashFunction(disease);
    Bucket *b = findBucket(disease);
    bool found = false;
    if(b != NULL) { // check possible buckets 
        Pair* p = b->getKeys();
        while(p != NULL) { // search for right pair
            if(*p->data == disease) { // if found continue at its tree
                found = true;
                p->tree->numCurrentPatientsDisease(p->tree->root);
            }

            p = p->next;
            if(p == NULL) {
                b = b->getNext();
                if(b == NULL || b->getValue() != val) {
                    break;
                } else {
                    p = b->getKeys();
                }
            }
        }
    }

    if(!found) { // if not print message
        cout << "There is no such disease in database!" << endl;
    }
}

void HashTable::numCurrentPatients() {
    Bucket *b = head;
    Pair* p;
    // check all buckets and pairs and print each tree's counter of untreated patients
    while(b != NULL) {
        p = b->getKeys();
        while(p != NULL) {
            int counter=0;
            p->tree->numCurrentPatients(p->tree->root, &counter);
            cout << *p->data << " " << counter << endl;

            p = p->next;
        }

        b = b->getNext();
    }
}

void HashTable::globalDiseaseStats(std::string date1, std::string date2) {
    Bucket *b = head;
    Pair* p;
    // check all buckets and pairs and print each tree's counter of patients between those dates
    while(b != NULL) {
        p = b->getKeys();
        while(p != NULL) {
            int counter=0;
            p->tree->globalDiseaseStats(p->tree->root, date1, date2, &counter);
            cout << *p->data << " " << counter << endl;

            p = p->next;
        }

        b = b->getNext();
    }
}

void HashTable::globalDiseaseStats() {
    Bucket *b = head;
    Pair* p;
    // check all buckets and pairs and print each tree's size
    while(b != NULL) {
        p = b->getKeys();
        while(p != NULL) {
            // int counter=0;
            // p->tree->globalDiseaseStats(p->tree->root, &counter);
            cout << *p->data << " " << p->tree->getSize() << endl;

            p = p->next;
        }

        b = b->getNext();
    }
}

void HashTable::diseaseFrequency(std::string disease, std::string date1, std::string date2, std::string country) {
    int val = hashFunction(disease);
    Bucket *b = findBucket(disease);
    int counter = 0;
    // find right pair to continue at its tree
    if(b != NULL) {
        Pair* p = b->getKeys();
        while(p != NULL) {
            if(*p->data == disease) {
                p->tree->diseaseFrequency(p->tree->root, date1, date2, country, &counter);
                cout << *p->data << " " << counter << endl;
            }

            p = p->next;
            if(p == NULL) {
                b = b->getNext();
                if(b == NULL || b->getValue() != val) {
                    break;
                } else {
                    p = b->getKeys();
                }
            }
        }
    }
}

void HashTable::diseaseFrequency(std::string disease, std::string date1, std::string date2) {
    int val = hashFunction(disease);
    Bucket *b = findBucket(disease);
    int counter = 0;
    if(b != NULL) {
        Pair* p = b->getKeys();
        while(p != NULL) {
            if(*p->data == disease) {
                p->tree->globalDiseaseStats(p->tree->root, date1, date2, &counter);
                cout << *p->data << " " << counter << endl;
            }

            p = p->next;
            if(p == NULL) {
                b = b->getNext();
                if(b == NULL || b->getValue() != val) {
                    break;
                } else {
                    p = b->getKeys();
                }
            }
        }
    }
}

void HashTable::topk(List<HeapPair>* results, std::string data, std::string target){
    int val = hashFunction(data);
    Bucket *b = findBucket(data);
    // find right pair and give it results to fill the list with right values
    if(b != NULL) {
        Pair* p = b->getKeys();
        while(p != NULL) {
            if(data.compare(*p->data) == 0) {
                p->tree->topk(results, p->tree->root, target, NINF, INF);
                break;
            }

            p = p->next;
            if(p == NULL) {
                b = b->getNext();
                if(b == NULL || b->getValue() != val) {
                    break;
                } else {
                    p = b->getKeys();
                }
            }
        }
    }
}

void HashTable::topk(List<HeapPair>* results, std::string data, std::string target, std::string date1, std::string date2){
    int val = hashFunction(data);
    Bucket *b = findBucket(data);
    int counter = 0;
    if(b != NULL) {
        Pair* p = b->getKeys();
        while(p != NULL) {
            if(data.compare(*p->data) == 0) {
                p->tree->topk(results, p->tree->root, target, date1, date2);
                break;
            }

            p = p->next;
            if(p == NULL) {
                b = b->getNext();
                if(b == NULL || b->getValue() != val) {
                    break;
                } else {
                    p = b->getKeys();
                }
            }
        }
    }
}

