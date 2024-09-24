#ifndef ID3TAG_H
#define ID3TAG_H

typedef struct {
    char *title;        // TIT2
    char *artist;       // TPE1
    char *album;        // TALB
    char *genre;        // TCON
    int   track;          // TRCK
    int   year;           // TDRC

    char *file_path;
    

} ID3Tag;

ID3Tag *newID3Tag(const char *title, const char *artist, const char *album, int track, int year, const char *genre);
void freeID3Tag(ID3Tag *tag);

#endif // ID3TAGS_H
