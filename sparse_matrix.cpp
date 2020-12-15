#include "sparse_matrix.hpp"

Wordnode::Wordnode(int pos, int bow, float tfidf){
    all_words_pos = pos;
    bow = bow;
    tfidf = tfidf;
    best_words_pos = -1;   
}

Wordlist::Wordlist(){
    head = NULL;
    size =  0;
}

Wordlist::~Wordlist(){
    while(head != NULL){
        Wordnode* temp = head;
        head = head->next;
        delete temp;
    }
}

unsigned int Wordlist::get_size(){
    return size;
}

void Wordlist::push(int pos, int bow, float tfidf){
    Wordnode *n = new Wordnode(pos, bow, tfidf);
    n->next = head;        
    head = n;
    size++;   
}

void Wordlist::push(int pos, int best_pos, int bow, float tfidf){
    Wordnode *n = new Wordnode(pos, bow, tfidf);
    n->best_words_pos = best_pos;
    n->next = head;        
    head = n;
    size++;   
}

Wordnode* Wordlist::pop() {
    Wordnode* temp;
    temp = head;
    head = head->next;
    size--;
    return temp;
}

void Wordlist::remove_not_best(int* best_words_vector, int vector_size){
    Wordlist *new_list = new Wordlist();
    while(size != 0){
        Wordnode* temp = this->pop();
        for(int i = 0 ; i < vector_size ; i++){
            if(temp->all_words_pos == best_words_vector[i]){
                new_list->push(temp->all_words_pos, i, temp->bow, temp->tfidf);
                break;
            }
        }
        delete temp;
    }
    head = new_list->head;   
}

SM::SM(unsigned int new_size){
    size = new_size;
    file_vector = new Wordlist*[size];
    for(unsigned int i = 0 ; i < size ; i++){
        file_vector[i] = new Wordlist();
    }
}

SM::SM(Clique* list_of_entries, float* tfidf_sum_vector, float* idf_vector, Dict* all_words){
    size = list_of_entries->get_size();
    file_vector = new Wordlist*[size];
    Cliquenode* temp = list_of_entries->head;   //get head of entries list for parsing   
    
    for(unsigned int j = 0 ; j < size ; j++){   //for all entries
        
        file_vector[j] = new Wordlist();        //init wordlist of entry
        
        Entry* e;
        std::string word;

        int word_loc;                           //location of word in all words vector
        int word_counter = 0;                   //counter for words in entry specs 
        
        e = temp->data;                         //get the entry
        e->loc = j;                             //save row number as loc for entry

        int counter_array[all_words->get_size()] = { 0 };   //init counter array for this entry
        std::istringstream iss(e->specs_words);
        while(iss){                                         // for each word in the specs
            word_counter++;                                 //update word counter 
            iss >> word;
            word_loc = all_words->find_loc(all_words->root, word);  //find it's location in the all words vector
            counter_array[word_loc] = counter_array[word_loc] + 1;  //update parallel location in counter array 
        }
        for(unsigned int i = 0 ; i < all_words->get_size() ; i++) { //go through counter array
            if(counter_array[i] != 0){                              //if you find a word that exists in specs
                int bow = counter_array[i];                         //calculate it's bow
                float tfidf = (float)bow/(float)word_counter;       //calculate it's tfidf
                file_vector[j]->push(i, bow, tfidf);                //add it to the wordlist

                tfidf_sum_vector[i] = tfidf_sum_vector[i] + tfidf;  //increase tfidf sum vector
            }
        }
        temp = temp->next;  
    }
}

SM::~SM(){
    for(unsigned int i = 0 ; i < size ; i++){
        delete file_vector[i];
    }
}
