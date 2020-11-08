#include <iostream>
#include <string>
#include <dirent.h>
#include "entry.hpp"

int main() {
    DIR *dir_p;
    DIR *dir_f;
    struct dirent *folder;
    int sites_counter = 0;
    std::string* sites;
    std::string input_dir = "./Datasets/2013_camera_specs/";
    if ( (dir_p = opendir(input_dir.c_str())) == NULL ) {
        perror("can't open the given directory");
        exit(2);
    } else {
        while (folder = readdir(dir_p)) {
            if (folder->d_name != std::string(".") && folder->d_name != std::string("..")) {
                std::cout << "folder = " << folder->d_name << std::endl;
                // for each json use name for constructor
                std::string file_dir = "./Datasets/2013_camera_specs/";
                file_dir.append(folder->d_name);
                std::cout << file_dir << "\n";
                struct dirent *file;
                if ( (dir_f = opendir(file_dir.c_str())) == NULL ) {
                    perror("can't open the given directory");
                    exit(2);
                } else {
                    while (file = readdir(dir_f)) {
                        // std::cout << "folder = " << folder->d_name << "file = " << file->d_name << std::endl;
                        std::string id_str = file->d_name;
                        size_t lastdot = id_str.find_last_of(".");
                        if (lastdot == std::string::npos) {
                            // call entry constructor and insert to hashtable
                        } else {
                            id_str = id_str.substr(0, lastdot);
                            std::cout << "folder = " << folder->d_name << "file = " << id_str << std::endl;
                            // call entry constructor and insert to hashtable
                        }
                    }
                }
            } 
        }

        (void) closedir (dir_p);
    } 

    return 0;
}