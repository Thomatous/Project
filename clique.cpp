#include "clique.hpp"

//-------------------Cliquenode-------------------

Cliquenode::Cliquenode(Entry* e){
    data = e;
    next = NULL;
}

Cliquenode::~Cliquenode(){
    delete data;
}

//-------------------Clique-------------------
Clique::Clique(){
    head = NULL;
    size = 0;
}

Clique::~Clique(){
    while(head->next != NULL){
        Cliquenode* temp = head;
        head = head->next;
        delete temp;   
    }
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

Cliquenode* Clique::merge(Cliquenode* other_head){
    Cliquenode* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = other_head;
    return head;
}

bool Clique::find(Entry* e){
    Cliquenode* temp = head;
    while(temp->next != NULL){
        if(e->get_hashvalue() == temp->data->get_hashvalue()){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

