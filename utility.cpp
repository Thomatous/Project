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

// fills up bow anf tf_idf tables
void create_bow_and_tf(int** bow, float** tf_idf, Clique* list_of_entries, Bow* dictionary, int dictionary_size) {
    Cliquenode* temp = list_of_entries->head;
    Entry* e;
    std::string word;
    // int bow[list_of_entries->get_size()][dictionary_size];
    // int tf_idf[list_of_entries->get_size()][dictionary_size];
    int word_loc;
    int entry_counter = 0;
    int word_counter = 0;                           // keeps total number of description's words 
    // for each entry
    while(temp != NULL) {
        e = temp->data;
        e->loc = entry_counter;                     // save its row number of arrays
        std::istringstream iss(e->specs_words);
        // for each word in its description
        while(iss) {
            word_counter++; 
            iss >> word;
            word_loc = dictionary->find_loc(dictionary->root, word);
            if( word_loc != -1 ) {                  // if word exists in dictionary
                bow[entry_counter][word_loc] += 1;  // increase its value in bow table
            }
        }
        // after finishing bow table
        // run through it and create tf values 
        for(int i=0 ; i<dictionary_size ; i++) {
            tf_idf[entry_counter][i] = bow[entry_counter][i]/word_counter;
        }

        temp = temp->next;
        entry_counter++;
    }
}

// -----------------SORT-------------------------

void swap(void* a, void* b) {
    void* temp = a;
    a = b;
    b = temp;
}

int partition(float* idf, std::string* words, int low, int high) {
    float pivot = idf[high];
    int i = (low-1);

    for(int j=low ; j <= high-1 ; j++) {
        if(idf[j] <= pivot) {
            i++;
            swap(&idf[i], &idf[j]);
            swap(&words[i], &words[j]);
        }
    }

    swap(&idf[i+1], &idf[high]);
    swap(&words[i+1], &words[high]);
    return i+1;
}

void sort(float* idf, std::string* words, int low, int high) {
    if(low < high) {
        int pivot = partition(idf, words, low, high);

        sort(idf, words, low, pivot-1);
        sort(idf, words, pivot+1, high);
    }
}

#endif