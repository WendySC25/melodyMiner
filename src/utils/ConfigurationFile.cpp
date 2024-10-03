#include "include/ConfigurationFile.h"

std::string getDefaultMusicDirectory() {
    struct passwd *pw = getpwuid(getuid());
    return std::string(pw->pw_dir) + "/Music"; 
}

bool directoryExists(const std::string& path) {
    struct stat info;
    return (stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR));
}

void saveConfiguration(const std::string& path, const std::map<std::string, std::string>& config) {
    std::ofstream file(path);
    
    if (!file.is_open()) {
        std::cerr << "Error opening configuration file for writing." << std::endl;
        return;
    }

    for (const auto& pair : config) 
        file << pair.first << "=" << pair.second << std::endl;

    file.close();
}

std::map<std::string, std::string> loadConfiguration(const std::string& path, const std::string& userDirectory) {
    std::map<std::string, std::string> config;
    
    if (!userDirectory.empty() && directoryExists(userDirectory)) 
        config["music_directory"] = userDirectory;
    else {
        std::cerr << "User directory not valid. Using default configuration." << std::endl;
        config["music_directory"] = getDefaultMusicDirectory();
    }

    saveConfiguration(path, config);
    return config;
}