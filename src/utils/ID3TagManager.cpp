#include "include/ID3TagManager.h"

ID3TagManager::ID3TagManager(Database& db) : albumDAO(db), performerDAO(db), rolaDAO(db) {}

void ID3TagManager::addTagsToDatabase(const std::unique_ptr<ID3Tag>& tagPtr) {

        if(tagPtr) {    
            Album newAlbum(0,tagPtr->getPath(),tagPtr->getAlbum(),tagPtr->getYear());
            Performer newPerformer(0,2,tagPtr->getArtist());

            if(albumDAO.getIdByAttribute(newAlbum.getName()) != -1) {
            std::cout << "El album ya existe, no se insertará." << std::endl;
            } else albumDAO.add(newAlbum);

            if(performerDAO.getIdByAttribute(newPerformer.getName()) != -1) {
            std::cout << "El perfomer ya existe, no se insertará." << std::endl;
            } else  performerDAO.add(newPerformer);

            int id_album = albumDAO.getIdByAttribute(newAlbum.getName());
            int id_perfomer = performerDAO.getIdByAttribute(newPerformer.getName());

            Rola newRola(0,
                    id_perfomer,
                    id_album, 
                    tagPtr->getPath(),
                    tagPtr->getTitle(),
                    tagPtr->getTrack(),
                    tagPtr->getYear(),
                    tagPtr->getGenre());


            if(rolaDAO.getIdByAttribute(newRola.getPath()) != -1){
                std::cout << "La rola ya existe, no se insertará." << std::endl;
            } else rolaDAO.add(newRola);

        } else {
            std::cout << "ERROR ." << std::endl;
        }
    
}
