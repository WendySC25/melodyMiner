
#include <gtkmm/application.h>
#include <sys/stat.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <filesystem>

#include "src/gui/melodyMinerWindow.h"  
#include "include/database/DatabaseUtils.h"



bool createDatabaseDirectory(std::string& dbPath) {
  std::string homeDir = getenv("HOME"); 
  dbPath = homeDir + "/.local/share/melodyMiner/db/";
  std::filesystem::path path(dbPath);

  if (!std::filesystem::exists(path)) {

    try {
      std::filesystem::create_directories(path);
    } catch (const std::filesystem::filesystem_error& e) {
      std::cerr << "Error al crear directorios: " << e.what() << std::endl;
      return false; 
    }

  }

  dbPath += "melodyMiner_database.db"; 

  try {
    Database db(dbPath); 
  } catch (const std::exception& e) {
    std::cerr << "Error al conectar la base de datos: " << e.what() << std::endl;
    return false; 
  }
    
  return true; 
}

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create("org.gtkmm.example");

  std::string dbPath;
  if (!createDatabaseDirectory(dbPath)) {
    std::cerr << "No se pudo iniciar la aplicación." << std::endl;
    return 1; 
  }

  return app->make_window_and_run<MelodyMinerWindow>(argc, argv, dbPath);
}
