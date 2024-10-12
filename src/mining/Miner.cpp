#include "include/Miner.h"
#include "src/gui/MinerDialog.h"
#include "include/ID3Tag.h"

#include <iostream>
#include <memory>
#include <iomanip>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <chrono>
#include <functional>

#include <taglib/tag_c.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>

Miner::Miner(Database &db) :
  m_Mutex(),
  m_shall_stop(false),
  m_has_stopped(false),
  m_fraction_done(0.0),
  m_message(),
  tagManager(db)
{}

void Miner::findMusicFiles(const std::string& directory) {
    DIR* dir = opendir(directory.c_str());
    if (!dir) {
        std::cerr << "Failed to open directory: " << directory << " (" << strerror(errno) << ")" << std::endl;
        return; 
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; 
        }

        std::string fullPath = directory + "/" + entry->d_name;
        struct stat path_stat;
        if (stat(fullPath.c_str(), &path_stat) != 0) {
            std::cerr << "Failed to stat file: " << fullPath << " (" << strerror(errno) << ")" << std::endl;
            continue; 
        }

        if (S_ISDIR(path_stat.st_mode)) {
            findMusicFiles(fullPath); 
        } else if (entry->d_type == DT_REG && fullPath.substr(fullPath.find_last_of(".") + 1) == "mp3") {
            file_paths.push_back(fullPath);
        }
    }

    closedir(dir);
}

void Miner::get_data(double* fraction_done, Glib::ustring* message) const{
  std::lock_guard<std::mutex> lock(m_Mutex);
  if (fraction_done) *fraction_done = m_fraction_done;
  if (message) *message = m_message;
}

void Miner::stop_work(){
  std::lock_guard<std::mutex> lock(m_Mutex);
  m_shall_stop = true;
}

bool Miner::has_stopped() const{
  std::lock_guard<std::mutex> lock(m_Mutex);
  return m_has_stopped;
}

void Miner::mineTags(MinerDialog* caller, std::string directory){
  {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_has_stopped = false;
    m_fraction_done = 0.0;
    m_message = "";
  } 

    findMusicFiles(directory);
    size_t totalFiles = file_paths.size(); 
    std::cout << " ::::::::::::::::::::::: TAGS " << std::endl;
    for (size_t i = 0; i < totalFiles; ++i) {

      {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        std::lock_guard<std::mutex> lock(m_Mutex);
        const auto& filePath = file_paths[i];

        TagLib_File *file = taglib_file_new(filePath.c_str());

        if (file) {
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
            taglib_file_free(file);
            }
        }

        m_fraction_done = static_cast<double>(i + 1) / totalFiles;
        std::ostringstream ostr;
        ostr << (m_fraction_done * 100.0) << "% done\n";
        m_message += ostr.str() + file_paths[i] + "\n \n";

      if (m_fraction_done >= 1.0){
        m_message += "Finished";
        break;
      }

      if (m_shall_stop){
        m_message += "Stopped";
        break;
      }

    }

    caller->notify();
  }

  {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if(totalFiles == 0) { 
      m_fraction_done = 1;
      m_message += "No mp3 files to mine";
    }

    m_shall_stop = false;
    m_has_stopped = true;
  }

  caller->notify();
}


    


        