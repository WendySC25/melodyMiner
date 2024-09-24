#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <id3tag.h>

#include "include/miner.h"

Miner *newMiner(const char *directory) {
    Miner *miner = malloc(sizeof(Miner));
    if (!miner) {
        perror("Failed to allocate miner");
        return NULL;
    }
    
    miner->directory = strdup(directory); 
    miner->file_paths = NULL;
    miner->file_count = 0;
    miner->tags       = NULL;                  
    miner->tag_count  = 0;
    return miner;
}

void freeMiner(Miner *miner) {
    if (miner) {
        free(miner->directory);

        if (miner->file_paths != NULL) {
            for (int i = 0; i < miner->file_count; i++) 
                free(miner->file_paths[i]); 
            free(miner->file_paths); 
        }

        if (miner->tags != NULL) {
            for (int i = 0; i < miner->tag_count; i++) 
                freeID3Tag(&miner->tags[i]); 
            free(miner->tags);
        }
       
        free(miner); 
    }
}

void mineTags(Miner *miner) {
    miner->tags = malloc(miner->tag_count * sizeof(ID3Tag));

    
    for (int i = 0; i < miner->tag_count; i++) 
        miner->tags[i] = *newID3Tag("Sample Title", "Sample Artist", "Sample Album", i + 1, 2023, "Rock");
}

void scanDirectory(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) { 
            printf("Archivo encontrado: %s \n", entry->d_name);
        }

        if (entry->d_type == DT_DIR &&
            strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            scanDirectory(new_path); 
        }
    }

    closedir(dp);
}

void findMusicFiles(Miner *miner, const char *directory) {

    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory);

    if (!dir) {
        perror("Failed to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", directory, entry->d_name);

        struct stat path_stat;
        stat(full_path, &path_stat);
        if (S_ISDIR(path_stat.st_mode)) {
            findMusicFiles(miner, full_path);
        } else if (strstr(entry->d_name, ".mp3")) {
            
            miner->file_paths = realloc(miner->file_paths, (miner->file_count + 1) * sizeof(char *));
            if (!miner->file_paths) {
                perror("Failed to allocate memory for file paths");
                closedir(dir);
                return;
            }

            miner->file_paths[miner->file_count] = strdup(full_path);
            miner->file_count++;
        }
    }

    closedir(dir);
}
