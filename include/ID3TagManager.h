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


class ID3TagManager {
public:
    ID3TagManager(Database& db);
    void readTag(const std::string& filePath);
    

private:
    AlbumDAO albumDAO; 
    PerformerDAO performerDAO;
    RolaDAO rolaDAO;

    void addTagsToDatabase(const std::unique_ptr<ID3Tag>& tagPtr);
};

#endif 
