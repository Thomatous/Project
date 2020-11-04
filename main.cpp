#include <iostream>
#include <dirent.h>

int main() {
    DIR *dir_p;
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
            } 
        }

        (void) closedir (dir_p);
    } 

    return 0;
}