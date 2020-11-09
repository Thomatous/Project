#include <iostream>
#include <string>
#include "entry.hpp"
#include "avl.hpp"

int main() {
    std::cout << "Started." << std::endl;
    Entry *e1 = new Entry("e", "1");
    e1->print();
    std::cout << e1->get_hashvalue() << std::endl;
    
    Entry *e2 = new Entry("e", "2");
    e2->print();
    std::cout << e2->get_hashvalue() << std::endl;

    Entry *e3 = new Entry("e", "3");
    e3->print();
    std::cout << e3->get_hashvalue() << std::endl;

    Entry *e4 = new Entry("e", "4");
    Entry *e5 = new Entry("e", "5");
    Entry *e6 = new Entry("e", "6");

    AVL avl;
    avl.root = avl.insert(avl.root, e1);
    avl.root = avl.insert(avl.root, e2);
    avl.root = avl.insert(avl.root, e3);
    avl.root = avl.insert(avl.root, e4);
    avl.root = avl.insert(avl.root, e5);
    avl.root = avl.insert(avl.root, e6);

    avl.print_preorder(avl.root);
    std::cout << std::endl;
    std::cout << avl.search(avl.root, e1->get_hashvalue()) << std::endl;
    std::cout << avl.search(avl.root, 0) << std::endl;
    // std::cout << avl.search(avl.root, 0);

    // std::cout << "Root " <<avl.root->get_entry_hashvalue() << std::endl;
    // std::cout << "Left " <<avl.root->left->get_entry_hashvalue() << std::endl;
    // std::cout << "Right " <<avl.root->right->get_entry_hashvalue() << std::endl;


    return 0;
}