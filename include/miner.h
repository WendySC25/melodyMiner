#ifndef MINER_H
#define MINER_H

#include <iostream>
#include <vector>
#include <string>

#include "include/ID3Tag.h"

class Miner {

     private:
        std::string directory;
        std::vector<std::string> file_paths;
        std::vector<ID3Tag> tags;

    public:
        Miner(const std::string& directory);
        void findMusicFiles(const std::string& directory);
        void mineTags();

        
};

#endif // MINER_H
