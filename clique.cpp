#include "clique.hpp"

//-------------------Cliquenode-------------------

//cliquenode constructor
Cliquenode::Cliquenode(Entry* e){
    data = e;
    next = NULL;
}

//cliquenode destructor, doesnt destroy the entry it points to just unlinks it
Cliquenode::~Cliquenode(){
    data = NULL;
    next = NULL;
    // std::cout << "Cliquenode deleted!" << std::endl;
}

//-------------------Clique-------------------

//clique constructor
Clique::Clique(){
    different = new AntiClique();
    head = NULL;
    printed = false;
    destroyed = false;
    anti_printed = NULL;
    size = 0;
}

//clique destructor
Clique::~Clique(){
    // update_clique_ptrs(NULL);
    // update_different_ptrs(NULL);
    
    while(head != NULL){
        Cliquenode* temp = head;
        head = head->next;
        delete temp;
    }
    if ( different != NULL ) {
        delete different;
    }
    if(anti_printed != NULL) {
        delete[] anti_printed;
    }
}

//size getter
int Clique::get_size(){
    return size;
}

//returns true if clique lsit is empty
bool Clique::is_empty(){
    return size == 0;
}

//adds entry to the head of the clique
void Clique::push(Entry* e){
    Cliquenode *n = new Cliquenode(e);
    n->next = head;        
    head = n;
    size++;   
}

void Clique::push(Cliquenode* n){
    n->next = head;        
    head = n;
    size++;
}

//removes entry at the top of the list
Cliquenode* Clique::pop() {
    Cliquenode* temp;
    temp = head;
    head = head->next;
    size--;
    return temp;
}

//merges this clique list with the one given
//by popping and pushing the nodes
//deletes the other list
void Clique::merge(Clique* c){
    while( !(c->is_empty()) ) {
        // this->push(c->pop());
        Cliquenode* new_node = c->pop();
        this->push(new_node->data);
        delete new_node;
    }
    delete c;
}

void Clique::merge_different(Clique* c){
    while( !(c->different->is_empty()) ) {
        AntiCliquenode* new_node = c->different->pop();
        if( new_node->data->different )
            new_node->data->different->replace(c, this);
        if( !this->different->find(new_node->data) )
            this->different->push(new_node->data);
        delete new_node;
    }
    delete c->different;
    c->different = NULL;
}

void Clique::replace_different(Clique* rc){
    AntiCliquenode* temp = this->different->head;
    while( temp != NULL ) {
        if(temp->data->different != NULL)
            temp->data->different->replace(this, rc);
        temp = temp->next;
    }
}

//returns true if the entry exists somewhere in the clique
//false otherwise
bool Clique::find(Entry* e){
    Cliquenode* temp = head;
    while(temp != NULL){
        if(e->get_hashvalue() == temp->data->get_hashvalue()){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

//debug function, prints the list
void Clique::print(){
    std::cout << "Clique: " << std::endl;
    Cliquenode* temp = head;
    while(temp->next != NULL){
        temp->data->print();
        temp = temp->next;
    }
    temp->data->print();
    std::cout << std::endl;
}


//function that goes over every entry in the clique
//and updates their clique pointer to the given value
//used for unlinking in the clique destructor to avoid freeing smth twice
void Clique::update_clique_ptrs(Clique* address){
    Cliquenode* temp = head;
    while(temp != NULL){
        temp->data->clique = address;
        temp = temp->next;
    }
}