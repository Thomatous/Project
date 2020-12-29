#include "sparse_matrix.hpp"

Wordnode::Wordnode(std::string new_word, int pos, int new_bow, float new_tfidf){
    word = new_word;
    all_words_pos = pos;
    bow = new_bow;
    tfidf = new_tfidf;
    best_words_pos = -1;
    next = NULL;   
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

void Wordlist::decrease_size(){
    size--;
}

unsigned int Wordlist::get_size(){
    return size;
}

void Wordlist::push(std::string word, int pos, int bow, float tfidf){
    Wordnode *n = new Wordnode(word, pos, bow, tfidf);
    n->next = head;        
    head = n;
    size++;   
}

void Wordlist::push(std::string word, int pos, int best_pos, int bow, float tfidf){
    Wordnode *n = new Wordnode(word, pos, bow, tfidf);
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
    delete[] file_vector;
}


SM::SM(Clique* list_of_entries, std::string* all_words_vector, float* tfidf_sum_vector, float* idf_vector, Dict* all_words){
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
        for(unsigned int i = 0 ; i < all_words->get_size() ; i++) {         //go through counter array
            if(counter_array[i] != 0){                                      //if you find a word that exists in specs
                int bow = counter_array[i];                                 //calculate it's bow
                float tfidf = (float)bow/(float)word_counter;               //calculate it's tfidf
                file_vector[j]->push(all_words_vector[i], i, bow, tfidf);   //add it to the wordlist

                tfidf_sum_vector[i] = tfidf_sum_vector[i] + tfidf;  //increase tfidf sum vector
            }
        }
        temp = temp->next;  
    }
}

void SM::remove_not_best(Dict* best_words){
    for(unsigned int i = 0 ; i < size ; i++){   //for all entries
        Wordnode* curr_word_node = file_vector[i]->head;
        Wordnode* prev_word_node;

        while(curr_word_node != NULL){
            Dictnode * temp_dict_node = best_words->find_node(best_words->root ,curr_word_node->word);

            if(temp_dict_node != NULL){
                curr_word_node->best_words_pos = temp_dict_node->best_words_loc;

                prev_word_node = curr_word_node;
                curr_word_node = curr_word_node->next;
            }
            else{
                Wordnode* temp_word_node;
                if(curr_word_node != file_vector[i]->head){
                    temp_word_node = curr_word_node; 
                    
                    prev_word_node->next = curr_word_node->next;
                    curr_word_node = curr_word_node->next;
                }
                else{
                    temp_word_node = curr_word_node; 

                    file_vector[i]->head = file_vector[i]->head->next;
                    curr_word_node = file_vector[i]->head;
                }

                delete temp_word_node;
                file_vector[i]->decrease_size();
            }
        }
    }
}

void SM::get_bow_vector(unsigned int entry_loc, int* bow_vector){
    if(entry_loc > size){
        std::cout << "Invalid entry!" << std::endl;
        exit(1);
    }
    else{
        Wordnode* curr_word_node = file_vector[entry_loc]->head;
        while(curr_word_node != NULL){
            bow_vector[curr_word_node->best_words_pos] = curr_word_node->bow;   
            curr_word_node = curr_word_node->next;
        }
    }
}

void SM::get_tfidf_vector(unsigned int entry_loc, float* tfidf_vector){
    if(entry_loc > size){
        std::cout << "Invalid entry!" << std::endl;
        exit(1);
    }
    else{
        Wordnode* curr_word_node = file_vector[entry_loc]->head;
        while(curr_word_node != NULL){
            tfidf_vector[curr_word_node->best_words_pos] = curr_word_node->tfidf;   
            curr_word_node = curr_word_node->next;
        }
    }
}