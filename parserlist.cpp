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

std::string Parserlist::clean_up(){
    Parserlistnode* temp = head;
    std::string words;
    std::string stopwords[119] = {  "a", "able", "about", "across", "after", "all", "almost", "also",
                                    "am", "among", "an", "and", "any", "are", "as", "at", "be", "because",
                                    "been", "but", "by", "can", "cannot", "could", "dear", "did", "do", "does",
                                    "either", "else", "ever", "every", "for", "from", "get", "got", "had", "has",
                                    "have", "he", "her", "hers", "him", "his", "how", "however", "i", "if", "in", "into",
                                    "is", "it", "its", "just", "least", "let", "like", "likely", "may", "me", "might", "most",
                                    "must", "my", "neither", "no", "nor", "not", "of", "off", "often", "on", "only", "or", "other",
                                    "our", "own", "rather", "said", "say", "says", "she", "should", "since", "so", "some", "than", "that",
                                    "the", "their", "them", "then", "there", "these", "they", "this", "tis", "to", "too", "twas", "us", "wants",
                                    "was", "we", "were", "what", "when", "where", "which", "while", "who", "whom", "why", "will", "with", "would", "yet",
                                    "you", "your" };
                            
    while(temp != NULL){
        words += temp->var_content + " ";
        temp=temp->next;
    }
    for (unsigned int i=0; i < words.length(); i++){    //for every letter   
        words[i] = std::tolower(words[i]);              //turn string lowercase
        if (ispunct(words[i])) { 
            words.replace(i--, 1, " ");                 //remove punctuation
        }              
    }
    std::stringstream sw(words);
    std::string w;
    words = "";
    while(std::getline(sw, w, ' ')){
        if(w.size() > 0){
            bool flag = false;
            for(unsigned int i = 0 ; i < 119 ; i++){
                if(w == stopwords[i]){
                    flag = true;
                    break;
                }
            }
            if(!flag){
                words += w + " ";
            }
        }
    }
    return words;
}