#include "acutest.hpp"
#include "avl.hpp"
#include <cstdlib>
#include <ctime>


void test_treenode_create(void) {
    Entry *e = new Entry("e", "0");
    Treenode t(e);

	TEST_ASSERT(t.get_height() == 1);
    TEST_ASSERT(t.left == NULL);
    TEST_ASSERT(t.right == NULL);
    TEST_ASSERT(t.get_entry() == e);
}

void test_avl_create(void) {
    AVL a;

    TEST_ASSERT(a.get_size() == 0);
    TEST_ASSERT(a.root == NULL);
}

void test_avl_insert(void) {
    srand(time(NULL));
    AVL a;
    int n=10;

    for(int i=0 ; i < n ; i++){
        Entry *e = new Entry( std::to_string(rand()%1000), std::to_string(rand()%1000));
        a.root = a.insert(a.root, e);
    }
    TEST_ASSERT(a.get_size() == n);
    bool flag = false;
    if(a.get_balance(a.root) == -1 || a.get_balance(a.root) == 0 || a.get_balance(a.root) == 1) flag = true;
    TEST_ASSERT(flag == true);
}


void test_avl_search(void) {
    AVL a;

    int n=100;
    Entry *lastElement;
    for(int i=0 ; i < n ; i++){
        Entry *e = new Entry("e", std::to_string(i));
        lastElement = e;
        a.root = a.insert(a.root, e);
    }
    unsigned long long h = hash_value_calculator("a","-1");
    TEST_ASSERT(a.search(a.root, lastElement->get_hashvalue()) == lastElement);
    TEST_ASSERT(a.search(a.root, h) == NULL);
}

TEST_LIST = {
	{ "test_treenode_create", test_treenode_create },
	{ "test_avl_create", test_avl_create },
	{ "test_avl_insert", test_avl_insert },
	{ "test_avl_search", test_avl_search },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};