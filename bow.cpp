#include "bow.hpp"

//----------------------------------Bownode----------------------------------

//Bownode constructor
Bownode::Bownode(std::string new_data){
    data = new_data;

    left = right = NULL;
    height = 1;
}

//Bownode destructor
Bownode::~Bownode(){
    // std::cout << "Bownode deleted succesfully!" << std::endl;
}

//height setter
void Bownode::set_height(int h){
    height = h;
}

//height getter
unsigned int Bownode::get_height(){
    return height;
}

//data pointer getter
std::string Bownode::get_data(){
    return data;
}

//if the children of this Bownode have heights
//keep the largest of the two
void Bownode::update_height(){
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

int Bownode::get_vector_loc(){
    return vector_loc;
}

void Bownode::set_vector_loc(unsigned int l){
    vector_loc = l;
}

//------------------------------------Bow------------------------------------

//Bow constructor
Bow::Bow():root(NULL), size(0){
}

//Bow destructor
Bow::~Bow() {
    clear(root);                                                //recursive function that deletes the tree
    // std::cout << "Tree deleted succesfully!" << std::endl;
}

//recursive function that parses the tree and deletes it
void Bow::clear(Bownode* n) {
    if(n != NULL) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

//Bow size getter
unsigned int Bow::get_size(){
    return size;
}

//recursive function that checks if tree/subtree is balanced
// return positive if left has more weight, negative if left has less wight and zero if balanced
int Bow::get_balance(Bownode* n) { 
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
Bownode* Bow::right_rotate(Bownode* root) {
    Bownode* pivot = root->left;
    Bownode* x = pivot->right;

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
Bownode* Bow::left_rotate(Bownode* root) {
    Bownode* pivot = root->right;
    Bownode* x = pivot->left;

    pivot->left = root;
    root->right = x;

    root->update_height();
    pivot->update_height();

    return pivot;
}

//inserts data in the Bow tree and rebalances
Bownode* Bow::insert(Bownode* n, std::string r) {
    // std::cout << "Inserting " << r->get_hashvalue() << std::endl;
    if(n == NULL) {                                             //found and aprrpprite spot                                  
        size++;
        // std::cout << r->get_hashvalue() << "\n";
        return new Bownode(r);
    } 
    else if(r > n->get_data()) {    //if data date later insert to the right      
        n->right = insert(n->right, r);
    } 
    else if(r < n->get_data()) {  //if data date earlier insert to the left
        n->left = insert(n->left, r);
    }

    n->update_height();     //updatee the height  of the Bownode
    
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

//debug function for printing Bow tree preorder
void Bow::print_preorder(Bownode* n){
    if (n == NULL) 
        return; 
    std::cout << n->get_data() << std::endl;
    print_preorder(n->left); 
    print_preorder(n->right);
}

//parses the tree and looks for an data with a matching hashvalue
//returns null if it hasn't been found, and a pointer to the data if it has been found
bool Bow::find(Bownode* n, std::string r){
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

Bownode* Bow::add(Bownode* n, std::string r){
    std::stringstream sw(r);
    std::string w;
    while(std::getline(sw, w, ' ')){
        if(w.size() > 0){
            n = insert(n, w);
        }
    }
    return n;
}

void Bow::vectorify(Bownode* n, std::string* v, unsigned int* loc){
    if (n == NULL) 
        return; 
    v[*loc] = n->get_data();
    n->set_vector_loc(-1);
    *loc = *loc + 1;
    vectorify(n->left, v, loc);
    vectorify(n->right, v, loc);    
}

int Bow::find_loc(Bownode* n, std::string r){
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

void Bow::set_word_loc(Bownode* n, std::string r, int loc){
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

void Bow::best_words_vectorify(std::string* dictionary, std::string* best_words, float* idf_vector, float* best_words_idf, unsigned int N, unsigned int N_best){
    if(N_best > N){
        std::cout << "Error! Too many best words, can't generate best words vector!" << std::endl;
    }
    else{
        for(unsigned int i = 0 ; i < N_best ; i++){
            float min = idf_vector[0];
            unsigned min_pos = 0;
            for(unsigned int j = 0 ; j < N ; j++){
                if(idf_vector[j] < min){
                    min = idf_vector[j];
                    min_pos = j;
                }
            }
            best_words[i] = dictionary[min_pos];        //save that word
            best_words_idf[i] = idf_vector[min_pos];    //save it's idf
            
            std::cout << best_words[i] << ": " << best_words_idf[i];

            idf_vector[min_pos] = 999;
            set_word_loc(root,best_words[i], i);
        }
    }
}
