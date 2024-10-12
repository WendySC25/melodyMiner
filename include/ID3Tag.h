#ifndef ID3TAG_H
#define ID3TAG_H

#include <string>
#include <memory>  

/**
 * @class ID3Tag
 * @brief Represents metadata for an audio file.
 */
class ID3Tag {
public:
  /**
   * @brief Constructs an ID3Tag object.
   * @param title Title of the track.
   * @param artist Artist of the track.
   * @param album Album name.
   * @param genre Genre of the track.
   * @param track Track number.
   * @param year Release year.
   * @param path File path of the audio.
   */
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
  std::string title;
  std::string artist;
  std::string album;
  std::string genre;
  int track;
  int year;
  std::string path;
};

#endif // ID3TAG_H
