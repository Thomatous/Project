#ifndef _UTILITY_
#define _UTILITY_

#include <iostream>
#include "dict.hpp"
#include "clique.hpp"
#include <sstream> 
#include <string> 
#include <ctime>
#include "double_linked_list.hpp"
#include <fstream>

class Clique;
class DoubleLinkedNode;

unsigned long long hash_value_calculator(std::string, std::string);
void create_bow_and_tf(int**, float**, Clique*, Dict*);
void merge(float*, int*, int, int, int);
void mergeSort(float*, int*, int, int);
void swap(std::string*, std::string*);
void shuffle(std::string*, unsigned int);
void prediction_merge(DoubleLinkedNode**, int, int, int);
void prediction_mergeSort(DoubleLinkedNode**, int, int);
void print_output(Clique*, unsigned int*);
void create_train_set(std::string*, const unsigned int);

#endif