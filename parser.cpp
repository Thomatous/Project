#include "parser.hpp"

Parserlist* Parser::parse(std::string path){
    
    list = new Parserlist();

    std::string line;
    std::ifstream file(path);
    size_t pos, temp_pos;
    std::string var, content, temp;

    while (getline (file, line)) {
        // Output the text from the file
        // std::cout << line.length() << "\n";
        if(line.length() != 1){
            pos = line.find_first_of("\"");
            temp = line.substr(pos+1);
            temp_pos = temp.find_first_of("\"");
            var = temp.substr(0, temp_pos);
            temp = temp.substr(temp_pos+1);
            pos = temp.find_first_of("[");
            temp_pos = temp.find_first_of("\"");
            if ( pos == std::string::npos || (pos > temp_pos) ) {
                pos = temp.find_first_of("\"");
                temp = temp.substr(pos+1);
                temp_pos = temp.find_last_of("\"");
                content = temp.substr(0, temp_pos);
            } else {
                getline(file, line);
                pos = line.find_first_not_of(" \t\r\n");
                line = line.substr(pos);
                content = "";
                while( line != "]" && line != "],") {
                    pos = line.find_first_of("\"");
                    temp = line.substr(pos+1);
                    temp_pos = temp.find_last_of("\"");
                    content += temp.substr(0, temp_pos) + "/t";
                    
                    getline(file, line);
                    pos = line.find_first_not_of(" \t\r\n");
                    line = line.substr(pos);
                }
            }
            // std::cout << var + ": " << content << std::endl;
            list->push(var, content);
        }
    }
    // Close the file
    file.close();
    return list;
}

