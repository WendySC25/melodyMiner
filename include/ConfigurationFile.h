#ifndef CONFIGURATIONFILE_H
#define CONFIGURATIONFILE_H


#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib> 
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h> 

std::string getDefaultMusicDirectory();
bool directoryExists(const std::string& path);
void saveConfiguration(const std::string& path, const std::map<std::string, std::string>& config);
std::map<std::string, std::string> loadConfiguration(const std::string& path, const std::string& userDirectory);


#endif