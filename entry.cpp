#include "entry.hpp"

Entry::Entry(){
    id = "None";                //default value for not initialized id
    page_title = "None";        //dedefault value for not initialized page_tiyle
    conn_tree = new ConnectionTree();
}

//constructor for entries
//assignes values given
Entry::Entry(std::string new_page_title, std::string new_id){
    id = new_id;           
    page_title = new_page_title;
    loc = -1;
    clique = new Clique();
    clique->push(this);
    specs = NULL;
    //generating hashvalue for entry
    hashvalue = hash_value_calculator(new_page_title, new_id);
    conn_tree = new ConnectionTree();
}

Entry::Entry(std::string new_page_title, std::string new_id, Parserlist* list){
    id = new_id;           
    page_title = new_page_title;
    loc = -1;
    clique = new Clique();
    clique->push(this);
    specs = list;
    //generating hashvalue for entry
    hashvalue = hash_value_calculator(new_page_title, new_id);
    conn_tree = new ConnectionTree();
}

//entry destructor
Entry::~Entry(){
    Clique* cp;
    if(clique != NULL) {
        cp = clique;
        clique->update_clique_ptrs(NULL);
        int size = cp->size;
        for(int i=0 ; i < size ; i++) {
            delete cp->pop();
        }
        delete cp;
    }
    if(specs != NULL)
        delete specs;
        
    if(conn_tree != NULL)
        delete conn_tree;
}

//id getter
std::string Entry::get_id(){
    return id;
}

//page title getter
std::string Entry::get_page_title(){
    return page_title;
}

Parserlist* Entry::get_specs() {
    return specs;
}

//hashvalue getter
unsigned long long Entry::get_hashvalue(){
    return hashvalue;
}

//debug function prints entry strings
void Entry::print(){
    std::cout << page_title << "//" << id << std::endl;
}

//merges the clique of this entry with the given entry's clique
void Entry::merge(Entry *e){
    if(e->clique != clique){
        // clique->different->merge(e->clique->different);
        clique->merge(e->clique);           //call clique merrge
        clique->update_clique_ptrs(clique); //make all entries in the clique point to this new merged one
    }
}

//pushes given entry's clique to different list and vice versa
void Entry::differs_from(Entry *e) {
    if( !e->clique->different->find(clique) ) {
        e->clique->different->push(clique);
    }
    if( !clique->different->find(e->clique) ) {
        clique->different->push(e->clique);
    }
}