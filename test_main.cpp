#include <iostream>
#include <string>
#include "entry.hpp"
#include "avl.hpp"
#include "hashtable.hpp"
#include "clique.hpp"

int main() {
    std::cout << "Started." << std::endl;
    Entry *e1 = new Entry("e", "1");
    e1->print();
    // std::cout << e1->get_hashvalue() << std::endl;
    
    Entry *e2 = new Entry("e", "2");
    e2->print();
    // std::cout << e2->get_hashvalue() << std::endl;

    Entry *e3 = new Entry("e", "3");
    e3->print();
    // std::cout << e3->get_hashvalue() << std::endl;

    // e1->clique->print();
    e1->merge(e2);
    e2->merge(e1);
    e1->merge(e3);
    
    // e2->clique->print();
    // e1->clique->print();
    // e3->clique->print();
    // std::cout << e1->clique->get_size() << std::endl;

    
    Entry *e4 = new Entry("e", "4");
    Entry *e5 = new Entry("e", "5");
    Entry *e6 = new Entry("e", "6");

    e4->merge(e5);
    e4->merge(e6);
    e4->merge(e4);
    e1->merge(e4);
    e1->merge(e2);
    e1->clique->print();
    std::cout << "e1 " << e1->clique << std::endl;
    std::cout << "e2 " << e2->clique << std::endl;
    std::cout << "e3 " << e3->clique << std::endl;
    std::cout << "e4 " << e4->clique << std::endl;
    std::cout << "e5 " << e5->clique << std::endl;
    std::cout << "e6 " << e6->clique << std::endl;

    // AVL avl;
    // avl.root = avl.insert(avl.root, e1);
    // avl.root = avl.insert(avl.root, e2);
    // avl.root = avl.insert(avl.root, e3);
    // avl.root = avl.insert(avl.root, e4);
    // avl.root = avl.insert(avl.root, e5);
    // avl.root = avl.insert(avl.root, e6);

    // avl.print_preorder(avl.root);
    // std::cout << std::endl;
    // std::cout << avl.search(avl.root, e1->get_hashvalue()) << std::endl;
    // std::cout << avl.search(avl.root, 0) << std::endl;
    // // std::cout << avl.search(avl.root, 0);

    // // std::cout << "Root " <<avl.root->get_entry_hashvalue() << std::endl;
    // // std::cout << "Left " <<avl.root->left->get_entry_hashvalue() << std::endl;
    // // std::cout << "Right " <<avl.root->right->get_entry_hashvalue() << std::endl;

    // HashTable ht(5);
    // ht.insert(new Entry("a", "0"));
    // ht.insert(new Entry("b", "1"));
    // ht.insert(new Entry("c", "3"));
    // ht.insert(new Entry("d", "5"));
    // ht.insert(new Entry("e", "2"));
    // ht.insert(new Entry("f", "6"));
    // ht.insert(new Entry("g", "2"));
    // ht.insert(new Entry("h", "6"));
    

    return 0;
}