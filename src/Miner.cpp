#include "include/Miner.h"  
#include "include/ID3Tag.h"

#include <iostream>
#include <memory>

#include <dirent.h>
#include <sys/stat.h>
#include <cstring>


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
            std::cout << "Archivo encontrado: " << fullPath << std::endl;
        }
    }

    closedir(dir);
}

void Miner::mineTags() {
    tags.reserve(file_paths.size());  
    for (const auto& filePath : file_paths) {

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
                static_cast<int>(track),
                static_cast<int>(year)
            );

            tags.push_back(std::move(newTag));

            std::cout << "Título: " << tags.back()->getTitle() << std::endl;
            std::cout << "Artista: " << tags.back()->getArtist() << std::endl;
            std::cout << "Álbum: " << tags.back()->getAlbum() << std::endl;
            std::cout << "Género: " << tags.back()->getGenre() << std::endl;
            std::cout << "Año: " << tags.back()->getYear() << std::endl;
            std::cout << "Número de pista: " << tags.back()->getTrack() << std::endl;


        } else {
            std::cerr << "Failed to read tag for: " << filePath << std::endl;
        }

        taglib_file_free(file);
    }
}
