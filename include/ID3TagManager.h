#ifndef ID3TAGMANAGER_H
#define ID3TAGMANAGER_H

#include <vector>
#include <memory>  
#include "include/ID3Tag.h"
#include "include/database/DatabaseUtils.h"

class ID3TagManager {
public:
    ID3TagManager(Database& db);
    void addTagsToDatabase(const std::unique_ptr<ID3Tag>& tagPtr);

private:
    AlbumDAO albumDAO; 
    PerformerDAO performerDAO;
    RolaDAO rolaDAO;
};

#endif 
