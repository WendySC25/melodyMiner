#include "include/Miner.h"
#include "src/gui/MinerDialog.h"
#include "include/ID3Tag.h"


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
      std::lock_guard<std::mutex> lock(m_Mutex);
      const auto& filePath = file_paths[i];

      try {
	tagManager.readTag(filePath); 
      } catch (const std::exception& e) {
	std::cerr << "Error reading tag for file: " << filePath << " - " << e.what() << std::endl;
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


    


        
