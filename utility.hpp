#include <iostream>
#include "bow.hpp"
#include "clique.hpp"
#include <sstream> 
#include <string> 

unsigned long long hash_value_calculator(std::string, std::string);
int** create_bow_and_tf(Clique*, Bow*, int);