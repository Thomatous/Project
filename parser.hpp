#ifndef _PARSER_
#define _PARSER_

#include "parserlist.hpp"
#include <iostream>
#include <fstream> 
#include <string.h>

class Parser{
    private:
        Parserlist *list;
    public:
        Parserlist* parse(std::string);
};
#endif