#ifndef ALBUM_H
#define ALBUM_H

#include <string>

class Album {
public:
    Album(int id_album = 0, const std::string &path = "", 
          const std::string &name = "", int year = 0);

    // Getters
    int getIdAlbum() const;
    std::string getPath() const;
    std::string getName() const;
    int getYear() const;

    // Setters
    void setIdAlbum(int id_album);
    void setPath(const std::string &path);
    void setName(const std::string &name);
    void setYear(int year);

private:
    int id_album;
    std::string path;
    std::string name;
    int year;
};

#endif // ALBUM_H
