#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "entry.hpp"
#include "parser.hpp"
#include "bow.hpp"
#include <sstream>

int main(void){
    Bow bow;
    Parser p;
    Entry* e = new Entry("abcd", "1234", p.parse("./Datasets/2013_camera_specs/www.walmart.com/158.json"));
    std::cout << e->get_specs()->clean_up() << std::endl << std::endl;

    e->specs_words = e->get_specs()->clean_up();
    std::cout << e->specs_words << "\n";
    // std::stringstream sw(e->get_specs()->clean_up());
    // std::string w;
    // bow.add(e->specs_words);
    // while(std::getline(sw, w, ' ')){
    //     if(w.size() > 0){
    //         bow.push_if_not_exists(w);
    //     }
    // }
    // bow.root = bow.add(bow.root, e->specs_words, &(e->specs_words));
    // std::cout << bow.get_size() << std::endl;
    // bow.print_preorder(bow.root);
    // std::string v[bow.get_size()];
    // unsigned int i = 0;
    // bow.vectorify(bow.root, v, &i);

    // unsigned int N_best = 10;

    // std::cout << bow.find_loc(bow.root, "frame") << std::endl;
    // std::cout << bow.find_loc(bow.root, "curtain") << std::endl;
    // std::cout << bow.find_loc(bow.root, "aberration") << std::endl;
    delete e;
}