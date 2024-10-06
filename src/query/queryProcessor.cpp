#include "src/query/queryProcessor.h"

std::string join(const std::vector<std::string>& vec, const std::string& delim) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i + 1 != vec.size()) {
            oss << delim;
        }
    }
    return oss.str();
}


std::string processQuery(const std::string& query) {
    std::string sqlQuery = "SELECT * FROM rolas r";

    try {

        std::regex titleRegex("title\\[\\s*([^\\]]+)\\s*\\]");

        std::smatch titleMatch;
        if (std::regex_search(query, titleMatch, titleRegex)) {
            std::string titles = titleMatch[1].str();
            std::replace(titles.begin(), titles.end(), '|', ',');
            std::stringstream titleStream(titles);
            std::string title;
            std::vector<std::string> titleList;
            
            while (std::getline(titleStream, title, ',')) {
                titleList.push_back("r.title LIKE '%" + title + "%'");
            }
            sqlQuery += " WHERE (" + join(titleList, " OR ") + ")";
        }



    } catch (const std::regex_error& e) {
        std::cerr << "Regex error: " << e.what() << std::endl;
        return "";
    }

    return sqlQuery+";";
}
