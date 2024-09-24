#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/ID3Tag.h"

ID3Tag *newID3Tag(const char *title, const char *artist, const char *album, int track, int year, const char *genre) {

    ID3Tag *tag = malloc(sizeof(ID3Tag));
    if (!tag) {
        perror("Failed to allocate ID3Tags");
        return NULL;
    }
    
    tag->title = strdup(title);
    tag->artist = strdup(artist);
    tag->album = strdup(album);
    tag->track = track;
    tag->year = year;
    tag->genre = strdup(genre);
    
    return tag;
}

void freeID3Tag(ID3Tag *tag) {
    if (tag) {
        free(tag->title);
        free(tag->artist);
        free(tag->album);
        free(tag->genre);
        free(tag);
    }
}
