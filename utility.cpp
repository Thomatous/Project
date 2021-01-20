#include "utility.hpp"

unsigned long long hash_value_calculator(std::string page_title, std::string id) {
    //generating hashvalue for entry
    unsigned long long hashvalue = 5381;

    int c;
    const char* site_c = page_title.c_str();
    const char* id_c = id.c_str();

    while ( (c = *site_c++) )
        hashvalue = ((hashvalue << 5) + hashvalue) + c; /* hash * 33 + c */

    while ( (c = *id_c++) )
        hashvalue = ((hashvalue << 5) + hashvalue) + c; /* hash * 33 + c */

    return hashvalue;
}

// fills up bow anf tf_idf tables
void create_bow_and_tf(int** bow, float** tf_idf, Clique* list_of_entries, Dict* dictionary) {
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
                bow[entry_counter][word_loc] = bow[entry_counter][word_loc] + 1;  // increase its value in bow table
            }
        }
        // after finishing bow table
        // run through it and create tf values 
        for(int i=0 ; i < DICTIONARY_SIZE ; i++) {
            tf_idf[entry_counter][i] = (float)bow[entry_counter][i]/(float)word_counter;
            // if(tf_idf[entry_counter][i] != 0) {
            //     std::cout << tf_idf[entry_counter][i] << "\n";
            // }
        }

        temp = temp->next;
        entry_counter++;
    }
}

// -----------------SORT-------------------------

void merge(float* tfidf, int* words, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
 
    float L[n1], R[n2];
    int Ls[n1], Rs[n2];
 
    for (int i = 0; i < n1; i++) {
        L[i] = tfidf[l + i];
        Ls[i] = words[l+i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = tfidf[m + 1 + j];
        Rs[j] = words[m + 1 + j];
    }
 
    int i = 0;
    int j = 0;
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            tfidf[k] = L[i];
            words[k] = Ls[i];
            i++;
        }
        else {
            tfidf[k] = R[j];
            words[k] = Rs[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        tfidf[k] = L[i];
        words[k] = Ls[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        tfidf[k] = R[j];
        words[k] = Rs[j];
        j++;
        k++;
    }
}

void mergeSort(float* tfidf, int* words, int l, int r) {
    if(l>=r) {
        return;//returns recursively
    }
    int m = (l+r-1)/2;
    mergeSort(tfidf, words, l, m);
    mergeSort(tfidf, words, m+1, r);
    merge(tfidf, words, l, m, r);
}

void prediction_merge(DoubleLinkedNode** pairs, int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;
 
    DoubleLinkedNode *L[n1], *R[n2];
 
    for (int i = 0; i < n1; i++) {
        L[i] = pairs[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = pairs[m + 1 + j];
    }
 
    int i = 0;
    int j = 0;
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i]->pred <= R[j]->pred) {
            pairs[k] = L[i];
            i++;
        }
        else if(L[i]->pred > R[j]->pred) {
            pairs[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        pairs[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        pairs[k] = R[j];
        j++;
        k++;
    }
}

void prediction_mergeSort(DoubleLinkedNode** pairs, int l, int r){
   if(l>=r) {
        return;//returns recursively
    }
    int m = (l+r-1)/2;
    prediction_mergeSort(pairs, l, m);
    prediction_mergeSort(pairs , m+1, r);
    prediction_merge(pairs, l, m, r);
}

// -----------------SHUFFLE-------------------------

void swap(std::string* a, std::string* b) {
    std::string temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(std::string* array, unsigned int size) {
    srand(19);
    // int s1,s2;
    for(unsigned int i=0 ; i < size ; ++i) {
        // s1 = rand()%size;
        // s2 = rand()%size;
        swap(array[i], array[rand()%size]);
    }
}

// -----------------PRINTING-------------------------
void print_output(Clique* list_of_entries, unsigned int *output_lines_counter) {
    *output_lines_counter = 0;
    std::ofstream output;
    output.open("output.csv");
    output << "left_spec_id,right_spec_id,label\n";
    Cliquenode* c_n = list_of_entries->head;
    Clique* c = NULL;
    AntiClique* d = NULL; 
    while( c_n != NULL ) {    //parse list of entries
        c = c_n->data->clique;                  //get entry's clique
        int size = c->size;
        // if( c->size == 1) {                     //if not similar to anyone keep it for validation
        //     single_entries.push(c_n->data);
        // }
        if( c->printed == false ) {                         //if not NULL
            // NOTE: replace till "c->printed = true;" with print_clique_Job add to queue
            Cliquenode* table[size];            //create table of clique's members
            Cliquenode* temp_entry = c->head;
            for(int i=0 ; i < size ; i++) {
                table[i] = temp_entry;
                temp_entry = temp_entry->next;
            }

            // print every possible pair from that clique
            for(int i=0 ; i<size ; i++) {       
                std::string url1 = table[i]->data->get_page_title() + "//" + table[i]->data->get_id();
                for(int j=i+1 ; j<size ; j++) {
                    std::string url2 = table[j]->data->get_page_title() + "//" + table[j]->data->get_id();
                    output << url1 << "," << url2 << ",1" <<  "\n";
                    ++(*output_lines_counter);
                }
                // table[i]->data->clique = NULL;  //make clique pointer NULL for all those entries so we don't print any pair more than once
            }
            c->printed = true;

            // print every possible negative similarity pair of entries
            d = c->different;                           // list of different cliques 
            if ( !d->is_empty() ) {
                // std::cout << d->size << std::endl;
                int d_size = d->size;
                
                if(c->anti_printed == NULL){
                    c->anti_printed = new Clique*[d_size];
                    for(int i=0 ; i < d_size ; i++) c->anti_printed[i] = NULL;
                }
            
                // adding all different cliques to d_table
                AntiCliquenode* d_table[d_size];
                AntiCliquenode* temp_d = d->head;
                for(int i=0 ; i<d_size ; i++) {
                    d_table[i] = temp_d;
                    temp_d = temp_d->next;
                }                

                for(int i=0 ; i<d_size ; i++) {         // for every different clique
                    Clique* d_c = d_table[i]->data;
                                        
                    if(d_c->anti_printed == NULL){
                        d_c->anti_printed = new Clique*[d_c->different->size];
                        for(int i=0 ; i < d_c->different->size ; i++) d_c->anti_printed[i] = NULL;
                    }

                    bool continue_flag = false;
                    for(int j = 0 ; j < d_size ; j++){
                        if(c->anti_printed[j] == d_c){
                            continue_flag = true;
                            break;
                        }
                    }
                    if(continue_flag == true) {
                        continue;    
                    } else {
                        for(int j = 0 ; j < d_size ; j++){
                            if(c->anti_printed[j] == NULL){
                                c->anti_printed[j] = d_c;
                                break;
                            }
                        }
                        for(int j = 0 ; j < d_c->different->size ; j++) {
                            if(d_c->anti_printed[j] == NULL){
                                d_c->anti_printed[j] = c;
                                break;
                            }
                        }
                    }

                    /*pthread_mutex_t* mutex;
                    pthread_mutex_init(mutex, NULL);
                    print_anticlique_Job paj(c, d_c, &output, &output_lines_counter, mutex);
                    paj.run();*/
                    // NOTE: to replace with add to job scheduler (args as above)
                    for(int j=0 ; j<size ; j++) {       // for every entry in c clique
                        Cliquenode* d_e = d_c->head;
                        std::string url1 = table[j]->data->get_page_title() + "//" + table[j]->data->get_id();
                        while( d_e != NULL ) {          // for every entry in different clique
                            std::string url2 = d_e->data->get_page_title() + "//" + d_e->data->get_id();
                            output << url1 << "," << url2 << ",0" <<  "\n";
                            ++(*output_lines_counter);
                            d_e = d_e->next;
                        }
                    }
                }
            }
        }
        c_n = c_n->next;
    }
    // NOTE: run printing tasks
    output.close();
}

void clear_print(Clique* list_of_entries) {
    if( remove( "output.csv" ) != 0 )
        perror( "Error deleting output" );
    Cliquenode* temp = list_of_entries->head;
    while(temp != NULL) {
        temp->data->clique->printed = false;
        if(temp->data->clique->anti_printed) {
            delete[] temp->data->clique->anti_printed;
            temp->data->clique->anti_printed = NULL;
        }
        temp = temp->next;
    }
}

void create_train_set(std::string* train_set, const unsigned int output_lines_counter) {
    std::ifstream input;
    input.open("output.csv");
    if ( input.is_open() ) {
        std::string empty;
        getline(input, empty);          // discard header line
        // fill up array with info lines
        for(unsigned int i=0 ; i < output_lines_counter ; ++i) {
            // NOTE: add read_output_Job to queue
            getline(input, train_set[i]);
            // pthread_mutex_t* mutex;
            // pthread_mutex_init(mutex, NULL);
            // read_output_Job roj(train_set, &input, i, mutex);
            // roj.run();
        }
        // NOTE: run reading output jobs
    } else {
        perror("no output file");
    }
    input.close();
}