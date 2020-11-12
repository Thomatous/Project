#ifndef _HASHVALUE_CALCULATOR
#define _HASHVALUE_CALCULATOR

#include "utility.hpp"

unsigned long long hash_value_calculator(std::string page_title, std::string id) {
    //generating hashvalue for entry
    unsigned long long hashvalue = 5381;

    int c;
    const char* site_c = page_title.c_str();
    const char* id_c = id.c_str();

    while (c = *site_c++)
        hashvalue = ((hashvalue << 5) + hashvalue) + c; /* hash * 33 + c */

    while (c = *id_c++)
        hashvalue = ((hashvalue << 5) + hashvalue) + c; /* hash * 33 + c */

    return hashvalue;
}

#endif