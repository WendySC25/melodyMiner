#include "include/ID3Tag.h"

ID3Tag::ID3Tag(const std::string& title, const std::string& artist, const std::string& album, 
               int track, int year, const std::string& genre)
    : title(title), artist(artist), album(album), track(track), year(year), genre(genre) {}

ID3Tag::~ID3Tag() {
    
}

std::string ID3Tag::getTitle() const {
    return title;
}

std::string ID3Tag::getArtist() const {
    return artist;
}

std::string ID3Tag::getAlbum() const {
    return album;
}

std::string ID3Tag::getGenre() const {
    return genre;
}

int ID3Tag::getTrack() const {
    return track;
}

int ID3Tag::getYear() const {
    return year;
}
