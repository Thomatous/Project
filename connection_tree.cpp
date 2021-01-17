#include "connection_tree.hpp"

//----------------------------------ConnectionNode----------------------------------

//ConnectionNode constructor
ConnectionNode::ConnectionNode(Entry* new_data){
    data = new_data;

    left = right = NULL;
    height = 1;
}

//ConnectionNode destructor
ConnectionNode::~ConnectionNode(){
    // std::cout << "ConnectionNode deleted succesfully!" << std::endl;
}

//height setter
void ConnectionNode::set_height(int h){
    height = h;
}

//height getter
unsigned int ConnectionNode::get_height(){
    return height;
}

//data pointer getter
Entry* ConnectionNode::get_data(){
    return data;
}

//if the children of this ConnectionNode have heights
//keep the largest of the two
void ConnectionNode::update_height(){
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

//------------------------------------ConnectionTree------------------------------------

//ConnectionTree constructor
ConnectionTree::ConnectionTree() {
    root = NULL;
    size = 0;
}

//ConnectionTree destructor
ConnectionTree::~ConnectionTree() {
    clear(root);                                                //recursive function that deletes the tree
    // std::cout << "Tree deleted succesfully!" << std::endl;
}

//recursive function that parses the tree and deletes it
void ConnectionTree::clear(ConnectionNode* n) {
    if(n != NULL) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

//ConnectionTree size getter
unsigned int ConnectionTree::get_size(){
    return size;
}

//recursive function that checks if tree/subtree is balanced
// return positive if left has more weight, negative if left has less wight and zero if balanced
int ConnectionTree::get_balance(ConnectionNode* n) { 
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
ConnectionNode* ConnectionTree::right_rotate(ConnectionNode* root) {
    ConnectionNode* pivot = root->left;
    ConnectionNode* x = pivot->right;

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
ConnectionNode* ConnectionTree::left_rotate(ConnectionNode* root) {
    ConnectionNode* pivot = root->right;
    ConnectionNode* x = pivot->left;

    pivot->left = root;
    root->right = x;

    root->update_height();
    pivot->update_height();

    return pivot;
}

//inserts data in the ConnectionTree tree and rebalances
ConnectionNode* ConnectionTree::insert(ConnectionNode* n, Entry* r) {
    // std::cout << "Inserting " << r->get_hashvalue() << std::endl;
    if(n == NULL) {                                             //found and aprrpprite spot                                  
        size++;
        ConnectionNode* t = new ConnectionNode(r);
        // std::cout << "New word:\t\t\t" << t->get_data() << "\t\t\tidf_count:\t\t\t" << t->idf_count << std::endl;
        return t;
    } 
    else if(r > n->get_data()) {    //if data date later insert to the right      
        n->right = insert(n->right, r);
    } 
    else if(r < n->get_data()) {  //if data date earlier insert to the left
        n->left = insert(n->left, r);
    }
    n->update_height();     //updatee the height  of the ConnectionNode
    
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

//parses the tree and looks for an data with a matching hashvalue
//returns null if it hasn't been found, and a pointer to the data if it has been found
bool ConnectionTree::find(ConnectionNode* n, Entry* r){
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