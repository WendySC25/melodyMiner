#include <iostream>
#include "include/Miner.h"
#include "include/Database.h"

// Test
#include "include/database/DatabaseUtils.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Use: " << argv[0] << " <directory>" << std::endl;
        return 1;
    }

    std::string directory = argv[1];
    Miner miner(directory);
    miner.findMusicFiles(directory);
    miner.mineTags();   

    Database db("src/database/db/music_database.db");  
    db.createTables(); 

    AlbumDAO albumDAO(db);
    Album newAlbum(0, "queso", "quesos", 2024);
    albumDAO.add(newAlbum);

    std::vector<Album> mios = albumDAO.getAll();
    for(auto album : mios){
        std::cout << album.getIdAlbum() << " " << album.getName() << " " << album.getPath() << " " << album.getYear() << std::endl;
    }

    std::cout << std::endl;

    PerformerDAO performerDAO(db);
    Performer performer(2, 2, "pancitop");
    performerDAO.add(performer);

    std::vector<Performer> tuyos = performerDAO.getAll();

    for(auto perfomer : tuyos){
        std::cout << perfomer.getName()  << std::endl;
    }








    return 0;
}
