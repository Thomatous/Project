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

    Clique cl;
    std::cout<< cl.get_size() << std::endl;

    cl.push(e1);
    cl.push(e2);
    cl.print();
    // std::cout<< cl.get_size() << std::endl;

    Clique cl2;
    cl2.push(e3);
    cl2.print();

    cl.merge(&cl2);
    cl.print();
    // std::cout<< cl.get_size() << std::endl;
    cl2.print();


    // Entry *e4 = new Entry("e", "4");
    // Entry *e5 = new Entry("e", "5");
    // Entry *e6 = new Entry("e", "6");

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