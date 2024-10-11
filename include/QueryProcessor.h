#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <sstream>

std::string join(const std::vector<std::string>& vec, const std::string& delim);
std::regex generateRegex(const std::string& field);
std::string getCondition(const std::string& field, const std::string& query, const std::string& con);
std::string processQuery(const std::string& query);



#endif
