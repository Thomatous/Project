#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "entry.hpp"
#include "parser.hpp"

int main(void){
    Parser p;
    Entry* e = new Entry("abcd", "1234", p.parse("./Datasets/2013_camera_specs/www.ebay.com/24376.json"));
    std::cout << e->get_specs()->clean_up() << std::endl;
    delete e;
}