#include "include/database/models/Album.h"

// Constructor
Album::Album(int id_album, const std::string &path, 
             const std::string &name, int year)
    : id_album(id_album), path(path), name(name), year(year) {}

// Getters
int Album::getIdAlbum() const { return id_album; }
std::string Album::getPath() const { return path; }
std::string Album::getName() const { return name; }
int Album::getYear() const { return year; }

// Setters
void Album::setIdAlbum(int id_album) { this->id_album = id_album; }
void Album::setPath(const std::string &path) { this->path = path; }
void Album::setName(const std::string &name) { this->name = name; }
void Album::setYear(int year) { this->year = year; }
