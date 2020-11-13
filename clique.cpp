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
    
    while(head != NULL){
        Cliquenode* temp = head;
        head = head->next;
        delete temp;
    }
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

Cliquenode* Clique::pop() {
    Cliquenode* temp;
    temp = head;
    head = head->next;
    size--;
    return temp;
}

void Clique::merge(Clique* c){
    while( !(c->is_empty()) ) {
        Cliquenode* new_node = c->pop();
        this->push(new_node->data);
        delete new_node;
    }
    delete c;
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
