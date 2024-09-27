#ifndef ID3TAG_H
#define ID3TAG_H

#include <string>

class ID3Tag {

private:
    std::string title;   // TIT2
    std::string artist;  // TPE1
    std::string album;   // TALB
    std::string genre;   // TCON
    int track;           // TRCK
    int year;            // TDRC

public:
    ID3Tag(const std::string& title, const std::string& artist, const std::string& album, 
           int track, int year, const std::string& genre);
    
    ~ID3Tag();

    // Métodos de acceso (getters)
    std::string getTitle() const;
    std::string getArtist() const;
    std::string getAlbum() const;
    std::string getGenre() const;
    int getTrack() const;
    int getYear() const;


};

#endif // ID3TAG_H
