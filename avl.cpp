#include "avl.hpp"

//----------------------------------Treenode----------------------------------

//treenode constructor
Treenode::Treenode(Entry* new_entry){
    entry = new_entry;

    left = right = NULL;
    height = 1;
}

//treenode destructor
Treenode::~Treenode(){
    if(entry != NULL)
        delete entry;
    // std::cout << "Treenode deleted succesfully!" << std::endl;
}

//height setter
void Treenode::set_height(int h){
    height = h;
}

//height getter
unsigned int Treenode::get_height(){
    return height;
}

//hashvalue getter
unsigned long long Treenode::get_entry_hashvalue(){
    return entry->get_hashvalue();
}

//entry pointer getter
Entry* Treenode::get_entry(){
    return entry;
}

//if the children of this treenode have heights
//keep the largest of the two
void Treenode::update_height(){
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

//------------------------------------AVL------------------------------------

//avl constructor
AVL::AVL(){
    root = NULL;
    size = 0;
}

//avl destructor
AVL::~AVL() {
    clear(root);                                                //recursive function that deletes the tree
    // std::cout << "Tree deleted succesfully!" << std::endl;
}

//recursive function that parses the tree and deletes it
void AVL::clear(Treenode* n) {
    if(n != NULL) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

//avl size getter
unsigned int AVL::get_size(){
    return size;
}

//recursive function that checks if tree/subtree is balanced
// return positive if left has more weight, negative if left has less wight and zero if balanced
int AVL::get_balance(Treenode* n) { 
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
Treenode* AVL::right_rotate(Treenode* root) {
    Treenode* pivot = root->left;
    Treenode* x = pivot->right;

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
Treenode* AVL::left_rotate(Treenode* root) {
    Treenode* pivot = root->right;
    Treenode* x = pivot->left;

    pivot->left = root;
    root->right = x;

    root->update_height();
    pivot->update_height();

    return pivot;
}

//inserts entry in the AVL tree and rebalances
Treenode* AVL::insert(Treenode* n, Entry* r) {
    // std::cout << "Inserting " << r->get_hashvalue() << std::endl;
    if(n == NULL) {                                             //found and aprrpprite spot                                  
        size++;
        // std::cout << r->get_hashvalue() << "\n";
        return new Treenode(r);
    } 
    else if(r->get_hashvalue() > n->get_entry_hashvalue()) {    //if Entry date later insert to the right      
        n->right = insert(n->right, r);
    } 
    else if(r->get_hashvalue() <= n->get_entry_hashvalue() ) {  //if Entry date earlier insert to the left
        n->left = insert(n->left, r);
    }
    n->update_height();     //updatee the height  of the treenode
    
    int b = get_balance(n); //get the balance of hte subtree

    if(b > 1) {                                                     //if left has more weight than 1
        if(r->get_hashvalue() < n->left->get_entry_hashvalue()){    //left left case
            return right_rotate(n);                             
        } 
        else{                                                       //left right case
            n->left = left_rotate(n->left);
            return right_rotate(n);
        }
    } 
    else if(b < -1) {                                               //if right has more weight than 1
        if(r->get_hashvalue() > n->right->get_entry_hashvalue()) {  //right right case
            return left_rotate(n);
        } 
        else{                                                       //right left case
            n->right = right_rotate(n->right);
            return left_rotate(n);
        }
    }
    return n;
}

//debug function for printing avl tree preorder
void AVL::print_preorder(Treenode* n){
    if (n == NULL) 
        return; 
    std::cout << n->get_entry_hashvalue() << " ";
    print_preorder(n->left); 
    print_preorder(n->right);
}

//parses the tree and looks for an entry with a matching hashvalue
//returns null if it hasn't been found, and a pointer to the entry if it has been found
Entry* AVL::search(Treenode* n, unsigned long long hashvalue){
    if(n == NULL){
        return NULL;
    }
    else if(hashvalue < n->get_entry_hashvalue()){
        return search(n->left, hashvalue);
    }
    else if(hashvalue > n->get_entry_hashvalue()){
        return search(n->right, hashvalue);
    }
    else {
        return n->get_entry(); // We found the value.
    }
}