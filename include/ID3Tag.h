#ifndef ID3TAG_H
#define ID3TAG_H

#include <string>
#include <memory>  

class ID3Tag {
public:
    ID3Tag(const std::string& title, const std::string& artist, const std::string& album, const std::string& genre,
           int track, int year, const std::string& path);
    ~ID3Tag(); 

    const std::string& getTitle() const;
    const std::string& getArtist() const;
    const std::string& getAlbum() const;
    const std::string& getGenre() const;
    int getTrack() const;
    int getYear() const;

    const std::string& getPath() const;

private:
    std::string title;   // TIT2
    std::string artist;  // TPE1
    std::string album;   // TALB
    std::string genre;   // TCON
    int track;           // TRCK
    int year;            // TDRC

    std::string path;
};

#endif // ID3TAG_H
