#include "bow.hpp"

Bow::Bow(){
    head = NULL;
    size = 0;
}

Bow::~Bow(){
    while(head != NULL){
        Bownode* temp = head;
        head = head->next;
        delete temp;
    }
}

unsigned int Bow::get_size(){
    return size;
}

bool Bow::exists(std::string str){
    Bownode* temp = head;
    while(temp != NULL){
        if(str == temp->data){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void Bow::push_if_not_exists(std::string str){
    if(exists(str) == false){
        Bownode *n = new Bownode();   
        n->data = str;             
        n->next = head;        
        head = n;  
    }
}

void Bow::print(){
    std::cout << "Bag of words: ";
    Bownode* temp = head;
    while(temp != NULL){
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;   
}