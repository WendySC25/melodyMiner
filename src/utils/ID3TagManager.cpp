#include "include/ID3TagManager.h"

ID3TagManager::ID3TagManager(Database& db) : albumDAO(db), performerDAO(db), rolaDAO(db) {}

void ID3TagManager::addTagsToDatabase(const std::unique_ptr<ID3Tag>& tagPtr) {

        if(tagPtr) {

            Album newAlbum(0,tagPtr->getPath(),tagPtr->getAlbum(),tagPtr->getYear());
            Performer newPerformer(0,2,tagPtr->getArtist());

            int id_album = albumDAO.getIdByAttribute(newAlbum.getName());
            if(id_album == -1) id_album = albumDAO.add(newAlbum);
            newAlbum.setIdAlbum(id_album);

            int id_performer = performerDAO.getIdByAttribute(newPerformer.getName());
            if(id_performer == -1) id_performer = performerDAO.add(newPerformer);
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
                
        } else {
            std::cout << "ERROR ." << std::endl;
        }
    
}
