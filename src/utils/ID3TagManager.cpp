#include "include/ID3TagManager.h"

ID3TagManager::ID3TagManager(Database& db) : albumDAO(db), performerDAO(db), rolaDAO(db) {}

void ID3TagManager::addTagsToDatabase(const std::unique_ptr<ID3Tag>& tagPtr) {
  if (tagPtr) {
    Album newAlbum(0, tagPtr->getPath(), tagPtr->getAlbum(), tagPtr->getYear());
    Performer newPerformer(0, 2, tagPtr->getArtist());

    int id_album = albumDAO.getIdByAttribute(newAlbum.getName());
    if (id_album == -1) id_album = albumDAO.add(newAlbum);
    newAlbum.setIdAlbum(id_album);

    int id_performer = performerDAO.getIdByAttribute(newPerformer.getName());
    if (id_performer == -1) id_performer = performerDAO.add(newPerformer);
    newPerformer.setIdPerformer(id_performer);

    Rola newRola(0,
		 id_performer,
		 id_album, 
		 tagPtr->getPath(),
		 tagPtr->getTitle(),
		 tagPtr->getTrack(),
		 tagPtr->getYear(),
		 tagPtr->getGenre());

    int id_rola = rolaDAO.getIdByAttribute(newRola.getTitle());
    if (id_rola == -1) id_rola = rolaDAO.add(newRola);          
  }
}

void ID3TagManager::readTag(const std::string& filePath) {
  TagLib_File *file = taglib_file_new(filePath.c_str());

  if (file) {
    TagLib_Tag *tag = taglib_file_tag(file);
    if (tag) {
      const char *title = taglib_tag_title(tag);
      const char *artist = taglib_tag_artist(tag);
      const char *album = taglib_tag_album(tag);
      const char *genre = taglib_tag_genre(tag);
      uint64_t year = taglib_tag_year(tag);
      uint64_t track = taglib_tag_track(tag);

      auto newTag = std::make_unique<ID3Tag>(
					     (title && title[0] != '\0') ? std::string(title) : "Unknown",
					     (artist && artist[0] != '\0') ? std::string(artist) : "Unknown",
					     (album && album[0] != '\0') ? std::string(album) : "Unknown",
					     (genre && genre[0] != '\0') ? std::string(genre) : "Unknown",
					     (track > 0) ? static_cast<int>(track) : 0,  
					     (year > 0) ? static_cast<int>(year) : 2024,
					     filePath
					     );

      addTagsToDatabase(newTag);
      taglib_file_free(file);
    } else {
      std::cerr << "Failed to retrieve tags from file: " << filePath << std::endl;
      taglib_file_free(file);
    }
  } else {
    std::cerr << "Failed to open file: " << filePath << std::endl;
  }
}
