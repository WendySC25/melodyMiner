#include <iostream>
#include "include/Miner.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Use: " << argv[0] << " <directory>" << std::endl;
        return 1;
    }

    std::string directory = argv[1];
    Miner miner(directory);
    miner.findMusicFiles(directory);
    miner.mineTags();   

    return 0;
}
