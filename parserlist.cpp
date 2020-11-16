#include "parserlist.hpp"

Parserlistnode::Parserlistnode(std::string name, std::string content){
    var_name = name;
    var_content = content;
    next = NULL;
}

Parserlist::Parserlist(){
    head = NULL;
    size = 0;
}

Parserlist::~Parserlist(){
    while(head != NULL){
        Parserlistnode* temp = head;
        head = head->next;
        delete temp;
    }
}

int Parserlist::get_size(){
    return size;
}

void Parserlist::push(std::string name, std::string content){
    Parserlistnode *n = new Parserlistnode(name, content);
    n->next = head;        
    head = n;
    size++;   
}

void Parserlist::print(){
    Parserlistnode* temp = head;
    while(temp != NULL){
        std::cout << "\t" << temp->var_name << ": " << temp->var_content << "," << std::endl;
        temp=temp->next;
    }
}