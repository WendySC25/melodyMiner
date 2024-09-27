#ifndef MINER_H
#define MINER_H

#include <string>
#include <vector>
#include <memory>  

#include "ID3Tag.h"

class Miner {

    public:
        Miner(const std::string& dir) : directory(dir) {}
        void findMusicFiles(const std::string& directory);
        void mineTags();

    private:
        std::string directory;
        std::vector<std::string> file_paths; 
        std::vector<std::unique_ptr<ID3Tag> > tags; 
};


#endif // MINER_H
