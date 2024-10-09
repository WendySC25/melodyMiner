#include "include/Miner.h"  
#include "include/ID3Tag.h"

#include <iostream>
#include <memory>

#include <iomanip>

#include <dirent.h>
#include <sys/stat.h>
#include <cstring>

#include <functional>


#include <taglib/tag_c.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>


void Miner::findMusicFiles(const std::string& directory) {
    DIR* dir = opendir(directory.c_str());
    if (!dir) {
        perror("Failed to open directory");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; 
        }

        std::string fullPath = directory + "/" + entry->d_name;
        struct stat path_stat;
        stat(fullPath.c_str(), &path_stat);

        if (S_ISDIR(path_stat.st_mode)) {
            findMusicFiles(fullPath);
        } else if (entry->d_type == DT_REG && fullPath.substr(fullPath.find_last_of(".") + 1) == "mp3") {
            file_paths.push_back(fullPath);
            // std::cout << "Archivo encontrado: " << fullPath << std::endl;
        }
    }

    closedir(dir);
}

void Miner::mineTags(const std::function<void(double)>& progressCallback) {

    Database db("db/music_database.db");  
    ID3TagManager tagManager(db);

    tags.reserve(file_paths.size());  
    size_t totalFiles = file_paths.size(); 

    std::cout << " ::::::::::::::::::::::: TAGS " << std::endl;
    for (size_t i = 0; i < totalFiles; ++i) {
        const auto& filePath = file_paths[i];

        TagLib_File *file = taglib_file_new(filePath.c_str());
        if (!file) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            continue;
        }

        TagLib_Tag *tag = taglib_file_tag(file);
        if (tag) {

            const char *title = taglib_tag_title(tag);
            const char *artist = taglib_tag_artist(tag);
            const char *album = taglib_tag_album(tag);
            const char *genre = taglib_tag_genre(tag);
            uint64_t year = taglib_tag_year(tag);
            uint64_t track = taglib_tag_track(tag);

           auto newTag = std::make_unique<ID3Tag>(
                (title && title[0] != '\0') ? std::string(title) : "Unknown",
                (artist && artist[0] != '\0') ? std::string(artist) : "Unknown",
                (album && album[0] != '\0') ? std::string(album) : "Unknown",
                (genre && genre[0] != '\0') ? std::string(genre) : "Unknown",
                (track > 0) ? static_cast<int>(track) : 0,  
                (year > 0) ? static_cast<int>(year) : 2024,
                filePath
            );

            tagManager.addTagsToDatabase(newTag);


        } else {
            std::cerr << "Failed to read tag for: " << filePath << std::endl;
        }

        taglib_file_free(file);

        double progress = static_cast<double>(i + 1) / totalFiles;
        progressCallback(progress);
    }
    std::cout << std::endl; 
    std::cout << std::endl; 
}

