#include "include/Miner.h"
#include "include/ID3Tag.h"
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>

Miner::Miner(const std::string& directory) : directory(directory) {}

void Miner::findMusicFiles(const std::string& directory) {

    DIR* dir = opendir(directory.c_str());
    if (!dir) {
        perror("Failed to open directory");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
            continue;  
        

        std::string fullPath = directory + "/" + entry->d_name;
        struct stat path_stat;
        stat(fullPath.c_str(), &path_stat);

        if (S_ISDIR(path_stat.st_mode)) 
            findMusicFiles(fullPath);
        else if (entry->d_type == DT_REG && fullPath.substr(fullPath.find_last_of(".") + 1) == "mp3") {
            file_paths.push_back(fullPath);
            std::cout << "Archivo encontrado: " << fullPath << std::endl;
        }
    }

    closedir(dir);
}

void Miner::mineTags() {
    tags.reserve(file_paths.size());
    for (const auto& filePath : file_paths) {
        
    }
}

