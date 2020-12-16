#ifndef _UTILITY_
#define _UTILITY_

#include <iostream>
#include "dict.hpp"
#include "clique.hpp"
#include <sstream> 
#include <string> 
#include <ctime>

class Clique;

unsigned long long hash_value_calculator(std::string, std::string);
void create_bow_and_tf(int**, float**, Clique*, Dict*);
void merge(float*, std::string*, int, int, int);
void mergeSort(float*, std::string*, int, int);
void swap(std::string*, std::string*);
void shuffle(std::string*, unsigned int);

#endif