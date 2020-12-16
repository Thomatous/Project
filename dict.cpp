#include "Dict.hpp"

//----------------------------------Dictnode----------------------------------

//Dictnode constructor
Dictnode::Dictnode(std::string new_data){
    data = new_data;

    left = right = NULL;
    height = 1;
}

//Dictnode destructor
Dictnode::~Dictnode(){
    // std::cout << "Dictnode deleted succesfully!" << std::endl;
}

//height setter
void Dictnode::set_height(int h){
    height = h;
}

//height getter
unsigned int Dictnode::get_height(){
    return height;
}

//data pointer getter
std::string Dictnode::get_data(){
    return data;
}

//if the children of this Dictnode have heights
//keep the largest of the two
void Dictnode::update_height(){
    int left_height = 0;
    int right_height = 0;

    if(left != NULL) {
        left_height = left->height;
    }
    if(right != NULL) {
        right_height = right->height;
    }
    height = std::max(left_height, right_height) +1;
}

int Dictnode::get_vector_loc(){
    return vector_loc;
}

void Dictnode::set_vector_loc(unsigned int l){
    vector_loc = l;
}

//------------------------------------Dict------------------------------------

//Dict constructor
Dict::Dict():root(NULL), size(0){
}

//Dict destructor
Dict::~Dict() {
    clear(root);                                                //recursive function that deletes the tree
    // std::cout << "Tree deleted succesfully!" << std::endl;
}

//recursive function that parses the tree and deletes it
void Dict::clear(Dictnode* n) {
    if(n != NULL) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

//Dict size getter
unsigned int Dict::get_size(){
    return size;
}

//recursive function that checks if tree/subtree is balanced
// return positive if left has more weight, negative if left has less wight and zero if balanced
int Dict::get_balance(Dictnode* n) { 
    if(n == NULL) {
        return 0;
    }
    int left_height = 0;
    int right_height = 0;
    
    if(n->left != NULL) {
        left_height = n->left->get_height();
    }

    if(n->right != NULL) {
        right_height = n->right->get_height();
    }

    return left_height - right_height;
}

//rotates to the right
/*   y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \                                  / \
 T1  T2                               T2  T3*/
Dictnode* Dict::right_rotate(Dictnode* root) {
    Dictnode* pivot = root->left;
    Dictnode* x = pivot->right;

    pivot->right = root;
    root->left = x;

    root->update_height();
    pivot->update_height();

    return pivot;
}


//rotates to the left
/*   y                               x
    / \                             /  \
   x   T3                          T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3*/
Dictnode* Dict::left_rotate(Dictnode* root) {
    Dictnode* pivot = root->right;
    Dictnode* x = pivot->left;

    pivot->left = root;
    root->right = x;

    root->update_height();
    pivot->update_height();

    return pivot;
}

//inserts data in the Dict tree and rebalances
Dictnode* Dict::insert(Dictnode* n, std::string r, std::string *file_string) {
    // std::cout << "Inserting " << r->get_hashvalue() << std::endl;
    if(n == NULL) {                                             //found and aprrpprite spot                                  
        size++;
        Dictnode* t = new Dictnode(r);
        t->idf_count = 1;
        t->last_string = file_string;
        // std::cout << "New word:\t\t\t" << t->get_data() << "\t\t\tidf_count:\t\t\t" << t->idf_count << std::endl;
        return t;
    } 
    else if(r > n->get_data()) {    //if data date later insert to the right      
        n->right = insert(n->right, r, file_string);
    } 
    else if(r < n->get_data()) {  //if data date earlier insert to the left
        n->left = insert(n->left, r, file_string);
    }
    else{
        if(file_string != n->last_string){
            n->idf_count++;
            n->last_string = file_string;
            // std::cout << "idf increased:\t\t\t" << n->get_data() << "\t\t\tidf_count:\t\t\t" << n->idf_count << std::endl;
        }
    }

    n->update_height();     //updatee the height  of the Dictnode
    
    int b = get_balance(n); //get the balance of hte subtree

    if(b > 1) {                                                     //if left has more weight than 1
        if(r < n->left->get_data()){    //left left case
            return right_rotate(n);                             
        } 
        else{                                                       //left right case
            n->left = left_rotate(n->left);
            return right_rotate(n);
        }
    } 
    else if(b < -1) {                                               //if right has more weight than 1
        if(r > n->right->get_data()) {  //right right case
            return left_rotate(n);
        } 
        else{                                                       //right left case
            n->right = right_rotate(n->right);
            return left_rotate(n);
        }
    }
    return n;
}

//inserts data in the Dict tree and rebalances
Dictnode* Dict::insert(Dictnode* n, std::string r, int loc, int best_loc) {
    // std::cout << "Inserting " << r->get_hashvalue() << std::endl;
    if(n == NULL) {                                             //found and aprrpprite spot                                  
        size++;
        Dictnode* t = new Dictnode(r);
        t->set_vector_loc(loc);
        t->best_words_loc = best_loc;
        // std::cout << "New word:\t\t\t" << t->get_data() << "\t\t\tidf_count:\t\t\t" << t->idf_count << std::endl;
        return t;
    } 
    else if(r > n->get_data()) {    //if data date later insert to the right      
        n->right = insert(n->right, r, loc, best_loc);
    } 
    else if(r < n->get_data()) {  //if data date earlier insert to the left
        n->left = insert(n->left, r, loc, best_loc);
    }

    n->update_height();     //updatee the height  of the Dictnode
    
    int b = get_balance(n); //get the balance of hte subtree

    if(b > 1) {                                                     //if left has more weight than 1
        if(r < n->left->get_data()){    //left left case
            return right_rotate(n);                             
        } 
        else{                                                       //left right case
            n->left = left_rotate(n->left);
            return right_rotate(n);
        }
    } 
    else if(b < -1) {                                               //if right has more weight than 1
        if(r > n->right->get_data()) {  //right right case
            return left_rotate(n);
        } 
        else{                                                       //right left case
            n->right = right_rotate(n->right);
            return left_rotate(n);
        }
    }
    return n;
}


Dictnode* Dict::add(Dictnode* n, std::string r, std::string* file_string){
    std::stringstream sw(r);
    std::string w;
    while(std::getline(sw, w, ' ')){
        if(w.size() > 0){
            n = insert(n, w, file_string);
        }
    }
    return n;
}

//debug function for printing Dict tree preorder
void Dict::print_preorder(Dictnode* n){
    if (n == NULL) 
        return; 
    std::cout << n->get_data() << "idf_cout: " << n->idf_count << std::endl;
    print_preorder(n->left); 
    print_preorder(n->right);
}

void Dict::vectorify(Dictnode* n, std::string* v, float* idf, float* tfidf, unsigned int* loc, unsigned int files_count){
    if (n == NULL) 
        return; 
    v[*loc] = n->get_data();
    idf[*loc] = log((float)(files_count/n->idf_count));
    tfidf[*loc] = 0;
    n->set_vector_loc(*loc);
    *loc = *loc +1;
    vectorify(n->left, v, idf, tfidf, loc, files_count);
    vectorify(n->right, v, idf, tfidf, loc, files_count);    
}

void Dict::vectorify(Dictnode* n, std::string* v, float* idf, unsigned int* loc){
    if (n == NULL) 
        return; 
    v[*loc] = n->get_data();
    idf[*loc] = n->idf;
    n->set_vector_loc(*loc);
    *loc = *loc +1;
    vectorify(n->left, v, idf, loc);
    vectorify(n->right, v, idf, loc);    
}



void Dict::set_word_loc(Dictnode* n, std::string r, int loc){
    if(r < n->get_data()){
        set_word_loc(n->left, r, loc);
    }
    else if(r > n->get_data()){
        set_word_loc(n->right, r, loc);
    }
    else if(r == n->get_data()){
        n->set_vector_loc(loc);
    }
}

//parses the tree and looks for an data with a matching hashvalue
//returns null if it hasn't been found, and a pointer to the data if it has been found
bool Dict::find(Dictnode* n, std::string r){
    if(n == NULL){
        return false;
    }
    else if(r < n->get_data()){
        return find(n->left, r);
    }
    else if(r > n->get_data()){
        return find(n->right, r);
    }
    else {
        return true; // We found the value.
    }
}

int Dict::find_loc(Dictnode* n, std::string r){
    if(n == NULL){
        return -1;
    }
    else if(r < n->get_data()){
        return find_loc(n->left, r);
    }
    else if(r > n->get_data()){
        return find_loc(n->right, r);
    }
    else {
        return n->get_vector_loc(); // We found the value.
    }
}

Dictnode* Dict::find_node(Dictnode* n, std::string r){
    if(n == NULL){
        return NULL;
    }
    else if(r < n->get_data()){
        return find_node(n->left, r);
    }
    else if(r > n->get_data()){
        return find_node(n->right, r);
    }
    else {
        return n; // We found the value.
    }
}

