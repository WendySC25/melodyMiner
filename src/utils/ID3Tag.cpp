#include "include/ID3Tag.h"



ID3Tag::ID3Tag(const std::string& title, const std::string& artist, const std::string& album, const std::string& genre,
               int track, int year, const std::string& path)
    : title(title), artist(artist), album(album), genre(genre), track(track), year(year), path(path) {}

ID3Tag::~ID3Tag() {
  
}

const std::string& ID3Tag::getTitle() const {
    return title;
}

const std::string& ID3Tag::getArtist() const {
    return artist;
}

const std::string& ID3Tag::getAlbum() const {
    return album;
}

const std::string& ID3Tag::getGenre() const {
    return genre;
}

int ID3Tag::getTrack() const {
    return track;
}

int ID3Tag::getYear() const {
    return year;
}


const std::string& ID3Tag::getPath() const {
    return path;
}

