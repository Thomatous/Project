#include "acutest.hpp"
#include "clique.hpp"

void test_cliquenode_create(void) {
    Entry e("e", "0");
    Cliquenode cliquenode(&e);

	TEST_ASSERT(cliquenode.data == &e);
	TEST_ASSERT(cliquenode.next == NULL);
}

void test_clique_create(void) {
    Clique clique;
    
	TEST_ASSERT(clique.head == NULL);
	TEST_ASSERT(clique.get_size() == 0);
    TEST_ASSERT(clique.is_empty() == true);
}

void test_clique_push(void) {
    Clique clique;
    
	int n = 100;
    for(int i = 0 ; i < n ; i++){
        Entry* e = new Entry("e", std::to_string(i));
        clique.push(e);
    }
    TEST_ASSERT(clique.head != NULL);
    TEST_ASSERT(clique.get_size() == n);
    TEST_ASSERT(clique.is_empty() == false);
    
    while(clique.head != NULL){
        Cliquenode* temp = clique.head;
        clique.head = clique.head->next;
        delete temp->data;
        delete temp;
    }
}

void test_clique_pop(void) {
    Clique clique;
    
	int n = 5;
    for(int i = 0 ; i < n ; i++){
        Entry* e = new Entry("e", std::to_string(i));
        clique.push(e);
    }

    Cliquenode *cliquenode;
    cliquenode = clique.pop();
    TEST_ASSERT(clique.get_size() == n-1);


    while(clique.head != NULL){
        Cliquenode* temp = clique.head;
        clique.head = clique.head->next;
        delete temp->data;
        delete temp;
    }
    delete cliquenode->data;
    delete cliquenode;
}

void test_clique_merge(void) {
    Clique *clique1 = new Clique();
    Clique *clique2 = new Clique();

    int n = 5;
    for(int i = 0 ; i < n ; i++){
        Entry* e = new Entry("e", std::to_string(i));
        clique1->push(e);
        Entry* n = new Entry("n", std::to_string(i));
        clique1->push(n);
    }
    int merged_size = clique1->get_size() + clique2->get_size();
    clique1->merge(clique2);
    clique2 = clique1;

    TEST_ASSERT(clique1->get_size() == merged_size);
    
    while(clique1->head != NULL){
        Cliquenode* temp = clique1->head;
        clique1->head = clique1->head->next;
        delete temp->data;
        delete temp;
    }
    delete clique1;
}

void test_clique_find(void) {
    Clique clique;
    Entry* lastElement;
    
	int n = 100;
    for(int i = 0 ; i < n ; i++){
        Entry* e = new Entry("e", std::to_string(i));
        lastElement = e;
        clique.push(e);
    }
    TEST_ASSERT(clique.find(lastElement) == true);
    Cliquenode *popped;
    popped = clique.pop();
    TEST_ASSERT(clique.find(popped->data) == false);
    
    while(clique.head != NULL){
        Cliquenode* temp = clique.head;
        clique.head = clique.head->next;
        delete temp->data;
        delete temp;
    }
    delete popped->data;
    delete popped;
}

void test_clique_update_clique_ptrs(void) {
    Entry* e = new Entry("e", "1");
    Clique* temp;
    temp = e->clique;
    e->clique->update_clique_ptrs(NULL);
    TEST_ASSERT(e->clique == NULL);
    delete temp;
    delete e;
}

TEST_LIST = {
	{ "test_cliquenode_create", test_cliquenode_create },
	{ "test_clique_create", test_clique_create },
    { "test_clique_push", test_clique_push },
    { "test_clique_pop", test_clique_pop },
    { "test_clique_merge", test_clique_merge },
    { "test_clique_find", test_clique_find },
    { "test_clique_update_clique_ptrs", test_clique_update_clique_ptrs },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};