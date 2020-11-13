#include "clique.hpp"

//-------------------Cliquenode-------------------

Cliquenode::Cliquenode(Entry* e){
    data = e;
    next = NULL;
}

Cliquenode::~Cliquenode(){
    data = NULL;
    next = NULL;
    // std::cout << "Cliquenode deleted!" << std::endl;
}

//-------------------Clique-------------------
Clique::Clique(){
    head = NULL;
    size = 0;
}

Clique::~Clique(){
    update_clique_ptrs(NULL);
    
    Cliquenode* temp = head;
    while(temp != NULL){
        delete temp;
        temp = temp->next;
    }
    head = NULL;   
    // std::cout << "Clique deleted!" << std::endl;
}

int Clique::get_size(){
    return size;
}

bool Clique::is_empty(){
    return size == 0;
}

void Clique::push(Entry* e){
    Cliquenode *n = new Cliquenode(e);
    n->next = head;        
    head = n;
    size++;   
}

void Clique::merge(Clique* c){
    Cliquenode* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = c->head;
    size += c->get_size();
    c->size = size;
    c->head = head;
}

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

void Clique::update_clique_ptrs(Clique* address){
    Cliquenode* temp = head;
    while(temp != NULL){
        temp->data->clique = address;
        temp = temp->next;
    }
}
