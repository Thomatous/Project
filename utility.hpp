#ifndef _UTILITY_
#define _UTILITY_

#include <iostream>
#include "dict.hpp"
#include "clique.hpp"
#include <sstream> 
#include <string> 

class Clique;

unsigned long long hash_value_calculator(std::string, std::string);
void create_bow_and_tf(int**, float**, Clique*, Dict*);
void merge(float*, int*, int, int, int);
void mergeSort(float*, int*, int, int);

#endif