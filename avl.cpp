#include "avl.hpp"

//----------------------------------Treenode----------------------------------
Treenode::Treenode(Entry* new_entry){
    entry = new_entry;

    left = right = NULL;
    height = 1;
}

Treenode::~Treenode(){
    delete entry;
    // std::cout << "Treenode deleted succesfully!" << std::endl;
}

void Treenode::set_height(int h){
    height = h;
}

unsigned int Treenode::get_height(){
    return height;
}

unsigned long long Treenode::get_entry_hashvalue(){
    return entry->get_hashvalue();
}

std::string Treenode::get_entry_full_name(){
    return entry->get_page_title() + "//" + entry->get_id();
}

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
AVL::AVL():root(NULL), size(0){
}

AVL::~AVL() {
    clear(root);
    std::cout << "Tree deleted succesfully!" << std::endl;
}

void AVL::clear(Treenode* n) {
    if(n != NULL) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

unsigned int AVL::get_size(){
    return size;
}

unsigned int AVL::get_balance(Treenode* n) { // return positive if left has more weight, negative if left has less wight and zero if balanced or null
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

Treenode* AVL::right_rotate(Treenode* root) {
    Treenode* pivot = root->left;
    Treenode* x = pivot->right;

    pivot->right = root;
    root->left = x;

    root->update_height();
    pivot->update_height();

    return pivot;
}

Treenode* AVL::left_rotate(Treenode* root) {
    Treenode* pivot = root->right;
    Treenode* x = pivot->left;

    pivot->left = root;
    root->right = x;

    root->update_height();
    pivot->update_height();

    return pivot;
}

Treenode* AVL::insert(Treenode* n, Entry* r) {
    // std::cout << "Inserting " << r->get_hashvalue() << std::endl;
    if(n == NULL) {
        size++;
        std::cout << r->get_hashvalue() << "\n";
        return new Treenode(r);
    } 
    else if(r->get_hashvalue() > n->get_entry_hashvalue()) { // if Entry date later insert to the right      
        n->right = insert(n->right, r);
    } 
    else if(r->get_hashvalue() <= n->get_entry_hashvalue() ) { // if Entry date earlier insert to the left
        n->left = insert(n->left, r);
    }
    n->update_height();
    
    int b = get_balance(n);

    if(b > 1) { // if left has more weight than 1
        if(r->get_hashvalue() < n->left->get_entry_hashvalue()){
            return right_rotate(n); 
        } 
        else{
            n->left = left_rotate(n->left);
            return right_rotate(n);
        }
    } 
    else if(b < -1) { //if right has more weight than 1
        if(r->get_hashvalue() > n->right->get_entry_hashvalue()) {
            return left_rotate(n);
        } 
        else{
            n->right = right_rotate(n->right);
            return left_rotate(n);
        }
    }
    return n;
}

void AVL::print_preorder(Treenode* n){
    if (n == NULL) 
        return; 
    std::cout << n->get_entry_hashvalue() << " ";
    print_preorder(n->left); 
    print_preorder(n->right);
}

std::string AVL::search(Treenode* n, unsigned long long hashvalue){
    if(n == NULL){
        return "Entry not in tree!";
    }
    if(hashvalue < n->get_entry_hashvalue()){
        return search(n->left, hashvalue);
    }
   if(hashvalue > n->get_entry_hashvalue()){
        return search(n->right, hashvalue);
    }
    return n->get_entry_full_name(); // We found the value.
}