#ifndef ROLA_H
#define ROLA_H

#include <include/database/models/Album.h>
#include <include/database/models/Performer.h>
#include <string>
#include <memory>

/**
 * @class Rola
 * @brief Represents a musical track with associated metadata.
 */
class Rola {
public:
  /**
   * @brief Constructs a Rola object.
   * @param id_rola Unique identifier for the track.
   * @param id_performer Identifier for the performer.
   * @param id_album Identifier for the album.
   * @param path File path to the track.
   * @param title Title of the track.
   * @param track Track number.
   * @param year Release year.
   * @param genre Genre of the track.
   */
  Rola(int id_rola = 0, int id_performer = 0, int id_album = 0, const std::string &path= "",
       const std::string &title= "", int track = 0, int year = 0, const std::string &genre = "" );

  int getIdRola() const;
  int getIdPerformer() const;
  int getIdAlbum() const;
  std::string getPath() const;
  std::string getTitle() const;
  int getTrack() const;
  int getYear() const;
  std::string getGenre() const;

  std::shared_ptr<Performer> getPerformer() const;
  std::shared_ptr<Album> getAlbum() const;

  void setIdRola(int id_rola);
  void setIdPerformer(int id_performer);
  void setIdAlbum(int id_album);
  void setPath(const std::string &path);
  void setTitle(const std::string &title);
  void setTrack(int track);
  void setYear(int year);
  void setGenre(const std::string &genre);

  void setPerformer(std::shared_ptr<Performer> performer);
  void setAlbum(std::shared_ptr<Album> album);

private:
  int id_rola;
  int id_performer;
  int id_album;
  std::string path;
  std::string title;
  int track;
  int year;
  std::string genre;

  std::shared_ptr<Performer> performer; 
  std::shared_ptr<Album> album; 
};

#endif // ROLA_H
