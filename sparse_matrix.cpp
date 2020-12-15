#include "sparse_matrix.hpp"

Wordnode::Wordnode(int pos, float bow, float tfidf){
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

void Wordlist::push(int pos, float bow, float tfidf){
    Wordnode *n = new Wordnode(pos, bow, tfidf);
    n->next = head;        
    head = n;
    size++;   
}

void Wordlist::push(int pos, int best_pos, float bow, float tfidf){
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

SM::~SM(){
    for(unsigned int i = 0 ; i < size ; i++){
        delete file_vector[i];
    }
}