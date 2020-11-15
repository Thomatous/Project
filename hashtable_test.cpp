#include "acutest.hpp"
#include "hashtable.hpp"
#include <time.h>

void test_create(void) {
    HashTable* ht = new HashTable(0);

    TEST_ASSERT(ht != NULL);
    TEST_ASSERT(ht->get_size() == 0);
    
    delete ht;
}

void test_insert_and_search(void) {
    HashTable* ht = new HashTable(1);
    srand(time(NULL));
    for(int i=0 ; i<10000 ; i++) {
        Entry* e = new Entry(std::to_string(rand()), std::to_string(rand()));
        ht->insert(e);
        TEST_ASSERT(ht->search(e->get_hashvalue()) == e);
    }

    delete ht;
}

TEST_LIST = {
	{ "hashtable_create", test_create },
	{ "hashtable_insert", test_insert_and_search },
	{ NULL, NULL }
};