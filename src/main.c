#include <stdio.h>
#include "include/ID3Tag.h"
#include "include/miner.h"

int main(void) {
    Miner *miner = newMiner("/Users/wendysc/Desktop/MUSIK");
    
    scanDirectory(miner->directory);
    findMusicFiles(miner, miner->directory);

    for (int i = 0; i < miner->file_count; i++) printf("SONG: %s ] \n", miner->file_paths[i]);
    freeMiner(miner);

    return 0;      
}
