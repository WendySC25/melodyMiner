#ifndef MINER_H
#define MINER_H

// #include <id3tag.h> 
#include "ID3Tag.h"

typedef struct {
    char *directory;    // Path of the directory to mine
    char **file_paths;  // Array of music files paths
    int file_count;
    ID3Tag *tags;       // Array of ID3Tags
    int tag_count;      
} Miner;

Miner *newMiner(const char *directory);
void freeMiner(Miner *miner);
void mineTags(Miner *miner);
void scanDirectory(const char *path);
void findMusicFiles(Miner *miner, const char *directory);


#endif 
