#ifndef ROLA_H
#define ROLA_H

#include <string>

class Rola {

public:
    Rola(int id_rola = 0, int id_performer = 0, int id_album = 0, const std::string &path= "",
         const std::string &title= "", int track = 0, int year = 0, const std::string &genre = "" );

    // Getters
    int getIdRola() const;
    int getIdPerformer() const;
    int getIdAlbum() const;
    std::string getPath() const;
    std::string getTitle() const;
    int getTrack() const;
    int getYear() const;
    std::string getGenre() const;

    // Setters
    void setIdRola(int id_rola);
    void setIdPerformer(int id_performer);
    void setIdAlbum(int id_album);
    void setPath(const std::string &path);
    void setTitle(const std::string &title);
    void setTrack(int track);
    void setYear(int year);
    void setGenre(const std::string &genre);

private:
    int id_rola;
    int id_performer;
    int id_album;
    std::string path;
    std::string title;
    int track;
    int year;
    std::string genre;

};

#endif // ROLA_H
