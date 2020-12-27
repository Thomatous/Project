#include <time.h>
#include <cstdlib>
#include "acutest.hpp"
#include "hashtable.hpp"
#include "entry.hpp"
#include "parser.hpp"
#include "avl.hpp"
#include "sparse_matrix.hpp"
#include "logistic_regression.hpp"

//hashtable tests
void hashtable_create(void) {
    HashTable* ht = new HashTable(0);

    TEST_ASSERT(ht != NULL);
    TEST_ASSERT(ht->get_size() == 0);
    
    delete ht;
}

void hashtable_insert_and_search(void) {
    HashTable* ht = new HashTable(1);
    srand(time(NULL));
    for(int i=0 ; i<10000 ; i++) {
        Entry* e = new Entry(std::to_string(rand()), std::to_string(rand()));
        ht->insert(e);
        TEST_ASSERT(ht->search(e->get_hashvalue()) == e);
    }

    delete ht;
}

//entry tests
void entry_create(void) {
    Entry* e = new Entry("abcd", "1234");

    TEST_ASSERT(e != NULL);
    TEST_ASSERT(e->get_page_title() == "abcd");
    TEST_ASSERT(e->get_id() == "1234");
    
    delete e;
}

void entry_merge(void) {
    Entry *e1 = new Entry("e", "1");
    Entry *e2 = new Entry("e", "2");

    e1->merge(e2);
    TEST_ASSERT(e1->clique == e2->clique);
    
    delete e1;
    delete e2;
}

void entry_complicated_merge(void) {
    Entry *e1 = new Entry("e", "1");
    Entry *e2 = new Entry("e", "2");
    Entry *e3 = new Entry("e", "3");
    Entry *e4 = new Entry("e", "4");
    Entry *e5 = new Entry("e", "5");
    Entry *e6 = new Entry("e", "6");

    e1->merge(e2);
    e2->merge(e1);
    e1->merge(e3);
    e4->merge(e5);
    e4->merge(e6);
    e4->merge(e4);
    e1->merge(e4);
    e1->merge(e2);

    TEST_ASSERT(e1->clique == e2->clique
                && e2->clique == e3->clique
                && e3->clique == e4->clique
                && e4->clique == e5->clique
                && e5->clique == e6->clique);

    delete e1;
    delete e2;
    delete e3;
    delete e4;
    delete e5;
    delete e6;
}

void entry_parser(void) {
    Parser p;
    Entry* e = new Entry("abcd", "1234", p.parse("./Datasets/2013_camera_specs/www.ebay.com/24376.json"));

    TEST_ASSERT(e->get_specs()->get_size() == 12);
    delete e;
}

//avl tests
void treenode_create(void) {
    Entry *e = new Entry("e", "0");
    Treenode t(e);

	TEST_ASSERT(t.get_height() == 1);
    TEST_ASSERT(t.left == NULL);
    TEST_ASSERT(t.right == NULL);
    TEST_ASSERT(t.get_entry() == e);
}

void avl_create(void) {
    AVL a;

    TEST_ASSERT(a.get_size() == 0);
    TEST_ASSERT(a.root == NULL);
}

void avl_insert(void) {
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


void avl_search(void) {
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

//clique tests
void cliquenode_create(void) {
    Entry e("e", "0");
    Cliquenode cliquenode(&e);

	TEST_ASSERT(cliquenode.data == &e);
	TEST_ASSERT(cliquenode.next == NULL);
}

void clique_create(void) {
    Clique clique;
    
	TEST_ASSERT(clique.head == NULL);
	TEST_ASSERT(clique.get_size() == 0);
    TEST_ASSERT(clique.is_empty() == true);
}

void clique_push(void) {
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

void clique_pop(void) {
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

void clique_merge(void) {
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

void clique_find(void) {
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

void clique_update_clique_ptrs(void) {
    Entry* e = new Entry("e", "1");
    Clique* temp;
    temp = e->clique;
    e->clique->update_clique_ptrs(NULL);
    TEST_ASSERT(e->clique == NULL);
    delete temp;
    delete e;
}

//dict tests
void dictnode_create(void){
    Dictnode* d = new Dictnode("test");
    TEST_ASSERT(d->get_data() == "test");
    TEST_ASSERT(d->left == NULL);  
    TEST_ASSERT(d->right == NULL);

    delete d;
}

void dict_create(void){
    Dict* dc = new Dict();

    TEST_ASSERT(dc->root == NULL);

    delete dc;
}

void dict_insert(void){
    srand(time(NULL));
    Dict* dc = new Dict();

    int n=100;
    for(int i=0 ; i < n ; i++){
        dc->root = dc->insert(dc->root, "t" + std::to_string(i), rand()%1000, rand()%1000);
    }
    TEST_ASSERT(dc->root != NULL);
    TEST_ASSERT(dc->get_size() == n);

    delete dc;
}

void dict_add(void){
    std::string str = "add this string to the tree";
    Dict* dc = new Dict();
    dc->root = dc->add(dc->root, str, 0);
    TEST_ASSERT(dc->root != NULL);
    TEST_ASSERT(dc->get_size() == 6);

    delete dc;
}

void dict_vectorify(void){
    std::string str = "add this string to the tree";
    Dict* dc = new Dict();
    dc->root = dc->add(dc->root, str, 0);

    std::string dv[6];
    for(int i = 0 ; i < 6 ; i++) dv[i] = "-1";

    float df[6];
    for(int i = 0 ; i < 6 ; i++) df[i] = -1;
    
    unsigned int loc = 0;
    dc->vectorify(dc->root, dv, df, &loc);

    int count = 0;
    for(int i = 0 ; i < 6 ; i++){
        if(dv[i] != "-1"){
            count++;
        }
    }
    TEST_ASSERT(count == 6);

    count = 0;
    for(int i = 0 ; i < 6 ; i++){
        if(df[i] != -1){
            count++;
        }
    }
    TEST_ASSERT(count == 6);
    delete dc;
}

void dict_find(void){
    std::string str = "add this string to the tree";
    Dict* dc = new Dict();
    dc->root = dc->add(dc->root, str, 0);


    std::string dv[6];
    for(int i = 0 ; i < 6 ; i++) dv[i] = "-1";

    float df[6];
    for(int i = 0 ; i < 6 ; i++) df[i] = -1;
    
    unsigned int loc = 0;
    dc->vectorify(dc->root, dv, df, &loc);

    Dictnode* d = NULL;
    d = dc->find_node(dc->root, "string");
    TEST_ASSERT(d != NULL);

    int l = dc->find_loc(dc->root, "string");
    TEST_ASSERT(l == d->get_vector_loc());

    delete dc;
}

//anticlique tests
void anticliquenode_create(void){
    Clique clique;
    AntiCliquenode* a = new AntiCliquenode(&clique);

    TEST_ASSERT(a->data == &clique);
    delete a;
}

void anticlique_create(void){
    AntiClique* ac = new AntiClique();

    TEST_ASSERT(ac->head == NULL);
    TEST_ASSERT(ac->get_size() == 0);
    TEST_ASSERT(ac->is_empty() == true);

    delete ac;
}

void anticlique_push_pop(void){
    AntiClique* ac = new AntiClique();

    int n=100;
    for(int i=0 ; i < n ; i++){
        Clique* c = new Clique();
        ac->push(c);
    }
    TEST_ASSERT(ac->head != NULL);
    TEST_ASSERT(ac->get_size() == n);
    TEST_ASSERT(ac->is_empty() == false);

    AntiCliquenode* a = ac->pop();
    TEST_ASSERT(ac->get_size() == n-1);
    delete a->data;
    delete a;

    for(int i = 0 ; i < n-1 ; i++){
        a = ac->pop();
        delete a->data;
        delete a;
    }

    delete ac;
}

void anticlique_merge(void){
    AntiClique* ac1 = new AntiClique();
    AntiClique* ac2 = new AntiClique();

    int n=100;
    for(int i=0 ; i < n ; i++){
        Clique* c1 = new Clique();
        Clique* c2 = new Clique();
        ac1->push(c1);
        ac2->push(c2);
    }

    ac1->merge(ac2);
    TEST_ASSERT(ac1->get_size() == 2*n);

    for(int i = 0 ; i < 2*n ; i++){
        AntiCliquenode* a = ac1->pop();
        delete a->data;
        delete a;
    }

    delete ac1;
}

void anticlique_find(void){
    AntiClique* ac = new AntiClique();

    int n=100;
    Clique* cf;
    for(int i=0 ; i < n ; i++){
        Clique* c = new Clique();
        if(i == n/2){
            cf = c;
        } 
        ac->push(c);
    }
    bool f = ac->find(cf);
    TEST_ASSERT(f == true);
    
    for(int i = 0 ; i < n ; i++){
        AntiCliquenode* a = ac->pop();
        delete a->data;
        delete a;
    }
    delete ac;
}

void anticlique_remove(void){
    AntiClique* ac = new AntiClique();

    int n=100;
    Clique* cf;
    for(int i=0 ; i < n ; i++){
        Clique* c = new Clique();
        if(i == n/2){
            cf = c;
        } 
        ac->push(c);
    }
    ac->remove(cf);
    TEST_ASSERT(ac->find(cf) == false);
    delete cf;

    for(int i = 0 ; i < n-1 ; i++){
        AntiCliquenode* a = ac->pop();
        delete a->data;
        delete a;
    }
    delete ac;
}



//sparse matrix tests

void wordnode_create(void){
    Wordnode* w = new Wordnode("test", 1, 1, 1.1);
    TEST_ASSERT(w->next == NULL);
    TEST_ASSERT(w->word == "test");
    TEST_ASSERT(w->all_words_pos == 1);
    TEST_ASSERT(w->bow == 1);
    TEST_ASSERT(w->best_words_pos == -1);
    delete w; 
}

void wordlist_create(void){
    Wordlist *wl = new Wordlist();
    TEST_ASSERT(wl->head == NULL);
    delete wl;
}

void wordlist_push_pop(void){
    Wordlist* wl = new Wordlist();

    int n=100;
    for(int i=0 ; i < n ; i++){
        wl->push(std::to_string(i), i, i, (float)i);
    }
    TEST_ASSERT(wl->head != NULL);
    TEST_ASSERT(wl->get_size() == n);

    Wordnode* w = wl->pop();
    TEST_ASSERT(wl->get_size() == n-1);
    
    delete w;
    delete wl;
}

void sparse_matrix_create(void){
    int n = 100;
    SM* sm = new SM(n);
    TEST_ASSERT(sm->size == n);
    TEST_ASSERT(sm->file_vector != NULL);
    delete sm;
}

void sparse_matrix_complicated_create(void){
    Clique clique;
    
	int n = 100;
    for(int i = 0 ; i < n ; i++){
        Entry* e = new Entry("e", std::to_string(i));
        clique.push(e);
    }

}


TEST_LIST = {
	{ "hashtable_create", hashtable_create },
	{ "hashtable_insert", hashtable_insert_and_search },
    { "entry_create", entry_create },
	{ "entry_merge", entry_merge },
	{ "entry_complicated_merge", entry_complicated_merge },
    { "entry_parser", entry_parser },
    { "treenode_create", treenode_create },
	{ "avl_create", avl_create },
	{ "avl_insert", avl_insert },
	{ "avl_search", avl_search },
    { "cliquenode_create", cliquenode_create },
	{ "clique_create", clique_create },
    { "clique_push", clique_push },
    { "clique_pop", clique_pop },
    { "clique_merge", clique_merge },
    { "clique_find", clique_find },
    { "clique_update_clique_ptrs", clique_update_clique_ptrs },
    { "dictnode_create", dictnode_create },
    { "dict_create", dict_create },
    { "dict_insert", dict_insert },
    { "dict_add", dict_add },
    { "dict_vectorify", dict_vectorify },
    { "dict_find", dict_find },
    { "anticliquenode_create", anticliquenode_create },
    { "anticlique_create", anticlique_create },
    { "anticlique_push_pop", anticlique_push_pop },
    { "anticlique_merge", anticlique_merge },
    { "anticlique_find", anticlique_find },
    { "anticlique_remove", anticlique_remove },
    { "wordnode_create", wordnode_create },
    { "wordlist_create", wordlist_create },
	{ "wordlist_push_pop", wordlist_push_pop },
    { "sparse_matrix_create", sparse_matrix_create },
    { NULL, NULL }
};