#include "include/database/models/Rola.h"

// Constructor
Rola::Rola(int id_rola, int id_performer, int id_album, const std::string &path,
           const std::string &title, int track, int year, const std::string &genre)
    : id_rola(id_rola), id_performer(id_performer), id_album(id_album),
      path(path), title(title), track(track), year(year), genre(genre) {}

// Getters
int Rola::getIdRola() const { return id_rola; }
int Rola::getIdPerformer() const { return id_performer; }
int Rola::getIdAlbum() const { return id_album; }
std::string Rola::getPath() const { return path; }
std::string Rola::getTitle() const { return title; }
int Rola::getTrack() const { return track; }
int Rola::getYear() const { return year; }
std::string Rola::getGenre() const { return genre; }

// Setters
void Rola::setIdRola(int id_rola) { this->id_rola = id_rola; }
void Rola::setIdPerformer(int id_performer) { this->id_performer = id_performer; }
void Rola::setIdAlbum(int id_album) { this->id_album = id_album; }
void Rola::setPath(const std::string &path) { this->path = path; }
void Rola::setTitle(const std::string &title) { this->title = title; }
void Rola::setTrack(int track) { this->track = track; }
void Rola::setYear(int year) { this->year = year; }
void Rola::setGenre(const std::string &genre) { this->genre = genre; }
