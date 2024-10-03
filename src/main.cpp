#include <iostream>
#include "include/Miner.h"
#include "include/database/DatabaseUtils.h"
#include "include/ConfigurationFile.h"


int main(int argc, char* argv[]) {

    const std::string configPath = "config.config"; 
    std::string userDirectory;

    if(argc < 2) userDirectory = " ";
    else userDirectory = argv[1];
    auto config = loadConfiguration(configPath, userDirectory);

    if (config.find("music_directory") != config.end()) 
        std::cout << "Music Directory: " << config["music_directory"] << std::endl;
    
    std::string directory = config["music_directory"];
    Miner miner(directory);
    miner.findMusicFiles(directory);
    miner.mineTags();   

    Database db("db/music_database.db");  
    db.createTables(); 

    // AlbumDAO albumDAO(db);
    // Album newAlbum(0, "queso", "quesos", 2024);
    // albumDAO.add(newAlbum);

    // std::vector<Album> mios = albumDAO.getAll();
    // for(auto album : mios){
    //     std::cout << album.getIdAlbum() << " " << album.getName() << " " << album.getPath() << " " << album.getYear() << std::endl;
    // }

    // std::cout << std::endl;

    // PerformerDAO performerDAO(db);
    // Performer performer(2, 2, "pancitop");
    // performerDAO.add(performer);

    // std::vector<Performer> tuyos = performerDAO.getAll();

    // for(auto perfomer : tuyos){
    //     std::cout << perfomer.getName()  << std::endl;


    // }

    // GroupDAO groupDao(db);
    // Group grupo(1,"banda", "2023", "2024");
    // groupDao.add(grupo);

    // std::vector<Group> grupos = groupDao.getAll();

    // for(auto grupoA :  grupos)
    //     std::cout << grupoA.getName()  << std::endl;
    
    // PersonDAO personDAO(db);
    // Person persona(1,"ana","susana", "2020", "2120");
    // personDAO.add(persona);

    // std::vector<Person> personas = personDAO.getAll();

    // for(auto personaA :  personas)
    //     std::cout << personaA.getRealName()  << std::endl;


    // RolaDAO rolaDAO(db);
    // Rola rola(1,1,1,"PATH","TITLE",2024,2023,"GENRE");
    // rolaDAO.add(rola); 
    // std::vector<Rola> rolas = rolaDAO.getAll();
    // for (const auto& rolaA : rolas) {
    //     std::cout << rolaA.getTitle() << std::endl;
    // }


    // PerformerDAO performerDAO(db);
    // AlbumDAO albumDAO(db);
    // RolaDAO rolaDAO(db);


    // auto& tags = miner.getTags();
    // for (const auto& tag : tags) {

        
    // }










    return 0;
}
