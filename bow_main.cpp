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
    std::stringstream sw(e->get_specs()->clean_up());
    std::string w;

    while(std::getline(sw, w, ' ')){
        if(w.size() > 0){
            bow.push_if_not_exists(w);
        }
    }
    std::cout << bow.get_size() << std::endl;
    bow.print();
    delete e;
}