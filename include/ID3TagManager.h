#ifndef ID3TAGMANAGER_H
#define ID3TAGMANAGER_H

#include <vector>
#include <memory>  
#include "include/ID3Tag.h"
#include "include/database/DatabaseUtils.h"
#include <taglib/tag_c.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "ID3Tag.h"

/**
 * @class ID3TagManager
 * @brief Manages ID3 tags for audio files.
 */
class ID3TagManager {
public:
  /**
   * @brief Constructs an ID3TagManager.
   * @param db Reference to the database for tag management.
   */
  ID3TagManager(Database& db);

  /**
   * @brief Reads ID3 tags from a specified audio file.
   * @param filePath Path to the audio file.
   */
  void readTag(const std::string& filePath);

private:
  AlbumDAO albumDAO;        
  PerformerDAO performerDAO; 
  RolaDAO rolaDAO;          

  /**
   * @brief Adds tags to the database.
   * @param tagPtr Unique pointer to the ID3Tag.
   */
  void addTagsToDatabase(const std::unique_ptr<ID3Tag>& tagPtr);
};

#endif 
