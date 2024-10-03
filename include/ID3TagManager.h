#ifndef ID3TAGMANAGER_H
#define ID3TAGMANAGER_H

#include <vector>
#include <memory>  
#include "include/ID3Tag.h"
#include "include/database/DatabaseUtils.h"

class ID3TagManager {
public:
    ID3TagManager(Database& db);
    void addTagsToDatabase(const std::vector<std::unique_ptr<ID3Tag>>& tags);

private:
    AlbumDAO albumDAO; 
    PerformerDAO performerDAO;
    RolaDAO rolaDAO;
};

#endif 
