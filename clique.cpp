#include "clique.hpp"

//-------------------Cliquenode-------------------

Cliquenode::Cliquenode(Entry* e){
    data = e;
    next = NULL;
}

Cliquenode::~Cliquenode(){
    // std::cout << "Cliquenode deleted!" << std::endl;
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
        delete head;
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
    c->head = head;
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

