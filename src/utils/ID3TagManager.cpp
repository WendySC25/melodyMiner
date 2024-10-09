#include "include/ID3TagManager.h"

ID3TagManager::ID3TagManager(Database& db) : albumDAO(db), performerDAO(db), rolaDAO(db) {}

void ID3TagManager::addTagsToDatabase(const std::unique_ptr<ID3Tag>& tagPtr) {

        if(tagPtr) {

            Album newAlbum(0,tagPtr->getPath(),tagPtr->getAlbum(),tagPtr->getYear());
            Performer newPerformer(0,2,tagPtr->getArtist());

            //ESTO SE PUEDE MANEJER DE MEJOR FORMA. DESDE EL METODO ADD, QUE BUSQUE SI YA EXITE Y REGRESE SIEMPRE EL INDICE CORRECTO.

            int id_album = albumDAO.getIdByAttribute(newAlbum.getName());
            int id_performer = performerDAO.getIdByAttribute(newPerformer.getName());

            if(id_album != -1) std::cout << "El album ya existe, no se insertará." << std::endl;
            else id_album = albumDAO.add(newAlbum);

            std::cout << "ID ALBUM." << id_album<<  std::endl;
           
            

            if(id_performer != -1) std::cout << "El perfomer ya existe, no se insertará." << std::endl;
            else  id_performer = performerDAO.add(newPerformer);

             std::cout << "ID PERFORMER." << id_performer<<  std::endl;
    

            Rola newRola(0,
                    id_performer,
                    id_album, 
                    tagPtr->getPath(),
                    tagPtr->getTitle(),
                    tagPtr->getTrack(),
                    tagPtr->getYear(),
                    tagPtr->getGenre());

            // HAY UN PROBLEMA CON EL ID
            int id_rola = rolaDAO.getIdByAttribute(newRola.getTitle());
            if (id_rola == -1) {
                id_rola = rolaDAO.add(newRola);
                std::cout << "Nueva rola insertada con ID: " << id_rola << std::endl;
            } else {
                std::cout << "La rola ya existe, ID: " << id_rola << std::endl;
            }

        } else {
            std::cout << "ERROR ." << std::endl;
        }
    
}
