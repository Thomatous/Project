#ifndef _LIST_
#define _LIST_

#include <iostream>

template <typename Type> 
struct Node {
    Type data;
    Node* next;
};

template <typename Type> 
class List{
private:
    Node<Type>* head;
public:
    List();                 //constructor                     
    ~List();                //destructor
    void insert(Type);      //inserts at head
    void insert(Type, int); //inserts at given position
    Type remove();          //removes at head of list
    Type remove(int);       //removes at given position
    int search(Type);       //returns position of given element, returns -1 if not found
    void print();           //prints list
    int size();             //returns size
};

template<typename Type> 
List<Type>::List(){
    head = null;
}

template<typename Type> 
List<Type>::~List(){
    Node<Type> *temp;
    while(head->next){
        temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename Type> 
void List<Type>::insert(Type value){
    Node<Type> *n = new Node<Type>();   
    n->data = value;             
    n->next = head;        
    head = n;              
}

template<typename Type> 
void List<Type>::insert(Type value, int position){
    //TODO:
}

template<typename Type> 
Type List<Type>::remove(){
    if(head != null){
        Type t = head->data;
        Node<Type>* temp = head;
        head = head->next;
        delete temp;
        return t;
    }
}

template<typename Type> 
Type List<Type>::remove(int position){
    //TODO
}

template<typename Type> 
int List<Type>::search(Type value){
    Node<Type> *temp = head;
    int position = 0;
    bool found = false;

    while(temp->next){
        if(temp->data == value){
            found - true;
            break;
        }
        else{ 
            temp = temp->next;
        }
        position++;
    }
    delete temp;
    if found == true return position;
    else return -1;
}

template<typename Type> 
void List<Type>::print(){
    Node<Type> *temp = head;
    while(temp->next){
        std::cout << temp->data << " " << std::endl;
    }
}

template<typename Type> 
int List<Type>::size(){
    Node<Type> *temp = head;
    int size = 0;
    while(temp->next){
        size++;
    }
    return size;
}
#endif