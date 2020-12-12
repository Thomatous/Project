#include <iostream>
#include "bow.hpp"
#include "clique.hpp"
#include <sstream> 
#include <string> 

unsigned long long hash_value_calculator(std::string, std::string);
void create_bow_and_tf(int**, float**, Clique*, Bow*, int);
void swap(void* a, void* b);
int partition(float* idf, std::string* words, int low, int high);
void sort(float* idf, std::string* words, int low, int high);