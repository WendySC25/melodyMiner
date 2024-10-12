#ifndef MINER_H
#define MINER_H

#include <gtkmm.h>
#include <iostream>
#include <memory>
#include <iomanip>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <chrono>
#include <functional>
#include "include/ID3TagManager.h"

class MinerDialog;

/**
 * @class Miner
 * @brief Handles the extraction of ID3 tags from audio files.
 *
 * This class provides functionality to search for music files,
 * mine their tags, and manage progress reporting.
 */
class Miner {
public:
  /**
   * @brief Constructs a Miner instance.
   * @param db The database instance used for tag management.
   */
  Miner(Database &db);

  /**
   * @brief Mines tags from audio files in the specified directory.
   * @param caller Pointer to the dialog that initiated the mining process.
   * @param directory The directory to search for music files.
   */
  void mineTags(MinerDialog* caller, std::string directory);

  /**
   * @brief Finds music files within a given directory.
   * @param directory The directory to search.
   */
  void findMusicFiles(const std::string& directory);

  /**
   * @brief Retrieves the current progress and message.
   * @param fraction_done Pointer to store the completion fraction.
   * @param message Pointer to store a status message.
   */
  void get_data(double* fraction_done, Glib::ustring* message) const;

  /**
   * @brief Signals to stop the mining process.
   */
  void stop_work();

  /**
   * @brief Checks if the mining process has stopped.
   * @return True if the process has stopped, false otherwise.
   */
  bool has_stopped() const;

private:
  mutable std::mutex m_Mutex; 
  bool m_shall_stop;          
  bool m_has_stopped;          
  double m_fraction_done;      
  std::vector<std::string> file_paths; 
  Glib::ustring m_message;     
  ID3TagManager tagManager;    
};

#endif // MINER_H

