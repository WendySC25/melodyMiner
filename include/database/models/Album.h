#ifndef ALBUM_H
#define ALBUM_H

#include <string>

/**
 * @class Album
 * @brief Represents a music album with details such as path, name, and year.
 */
class Album {
public:
    /**
     * @brief Constructs an Album object.
     * @param id_album Unique identifier for the album.
     * @param path File path to the album.
     * @param name The name of the album.
     * @param year The release year of the album.
     */
    Album(int id_album = 0, const std::string &path = "", 
          const std::string &name = "", int year = 0);

    int getIdAlbum() const;
    std::string getPath() const;
    std::string getName() const;
    int getYear() const;

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
