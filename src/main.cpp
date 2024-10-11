#include <iostream>
#include "include/Miner.h"
#include "include/database/DatabaseUtils.h"
#include "include/ConfigurationFile.h"
#include "include/ID3TagManager.h"


int main(int argc, char* argv[]) {

    //Configuration
    const std::string configPath = "config.config"; 
    std::string userDirectory;

    if(argc < 2) userDirectory = " ";
    else userDirectory = argv[1];
    auto config = loadConfiguration(configPath, userDirectory);

    if (config.find("music_directory") != config.end()) 
        std::cout << "Music Directory: " << config["music_directory"] << std::endl;
    
    //Mining
    std::string directory = config["music_directory"];
    Miner miner;

    std::cout << " ::::::::::::::::::::::: MINING " << std::endl;
    miner.findMusicFiles(directory);
    miner.mineTags([](double progress) {

    std::cout << "Progreso: " << (progress * 100) << "%" << std::endl;
    });

    // //Database
    // Database db("db/music_database.db");  
    // db.createTables(); 

    // //Insert tags
    // ID3TagManager manager(db);
    // manager.addTagsToDatabase(miner.getTags());

    return 0;
}
