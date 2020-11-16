#include "parser.hpp"

Parserlist* Parser::parse(std::string path){
    
    list = new Parserlist();

    std::string line;
    std::ifstream file(path);
    size_t pos, temp_pos;
    std::string var, content, temp;

    while (getline (file, line)) {
        if(line.length() != 1){                                     //then it's not file start or file end
            pos = line.find_first_of("\"");                         //find first quotes
            temp = line.substr(pos+1);
            temp_pos = temp.find_first_of("\"");
            var = temp.substr(0, temp_pos);                         //save var name 
            temp = temp.substr(temp_pos+1);
            pos = temp.find_first_of("[");
            temp_pos = temp.find_first_of("\"");
            //check if content is string or array
            if ( pos == std::string::npos || (pos > temp_pos) ) {   //then content is string
                pos = temp.find_first_of("\"");
                temp = temp.substr(pos+1);
                temp_pos = temp.find_last_of("\"");
                content = temp.substr(0, temp_pos);
            } else {                                                //then content is array
                getline(file, line);
                pos = line.find_first_not_of(" \t\r\n");
                line = line.substr(pos);
                content = "";
                while( line != "]" && line != "],") {               //append the array's string in content
                    pos = line.find_first_of("\"");
                    temp = line.substr(pos+1);
                    temp_pos = temp.find_last_of("\"");
                    content += temp.substr(0, temp_pos) + "/t";
                    
                    getline(file, line);
                    pos = line.find_first_not_of(" \t\r\n");
                    line = line.substr(pos);
                }
            }
            list->push(var, content);                               //add var and content to list of json values
        }
    }
    file.close();
    return list;
}

