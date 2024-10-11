#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <sstream>

class QueryProcessor {

    public:
    QueryProcessor();
    std::string processQuery(const std::string& query);

    private:
    std::string join(const std::vector<std::string>& vec, const std::string& delim);
    std::regex getPattern(const std::string& field);
    std::string getCondition(const std::string& field, const std::string& query, const std::string& con, bool isString);

};


#endif
