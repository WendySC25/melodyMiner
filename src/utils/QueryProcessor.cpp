#include "include/QueryProcessor.h"

QueryProcessor::QueryProcessor(){}

std::string QueryProcessor::join(const std::vector<std::string>& vec, const std::string& delim) {
  std::ostringstream oss;
  for (size_t i = 0; i < vec.size(); ++i) {
    oss << vec[i];
    if (i + 1 != vec.size()) oss << delim;
  }
  return oss.str();
}

std::regex QueryProcessor::getPattern(const std::string& field) {
  return std::regex(field + "\\[\\s*([^\\]]+)\\s*\\]");
}

std::string QueryProcessor::getCondition(const std::string& field, const std::string& query, const std::string& con, bool isString){
  std::regex conditionRegex = getPattern(field);
  std::string condition = "";

  std::smatch conditionMatch;
  if (std::regex_search(query, conditionMatch, conditionRegex)) {
    std::string elements = conditionMatch[1].str();
            
    bool hasOr = elements.find('|') != std::string::npos;
    bool hasAnd = elements.find('&') != std::string::npos;

    if (hasOr) std::replace(elements.begin(), elements.end(), '|', ',');
    else if (hasAnd) std::replace(elements.begin(), elements.end(), '&', ',');

    std::stringstream elementsStream(elements);
    std::string element;
    std::vector<std::string> elementList;

    while (std::getline(elementsStream, element, ',')) {
      if(isString) elementList.push_back(con + " LIKE '%" + element + "%'");
      else elementList.push_back(con + " = " + element );
    }
            
    if (!elementList.empty()) {
      if (hasOr) condition = join(elementList, " OR ");
      else if (hasAnd) condition = join(elementList, " AND "); 
      else condition = elementList.front(); 
    }
  }
        
  return condition;
}

std::string QueryProcessor::processQuery(const std::string& query) {
  std::string sqlQuery = "SELECT * FROM rolas r";
    
  try {

    std::vector<std::string> conditions;

    conditions.push_back(getCondition("title", query, "r.title", true));
    conditions.push_back(getCondition("album", query, "a.name", true));
    conditions.push_back(getCondition("performer", query, "p.name", true));
    conditions.push_back(getCondition("year", query, "r.year", false));
    conditions.push_back(getCondition("genre", query, "r.genre",true));
    conditions.push_back(getCondition("track", query, "r.track",false));

    bool hasAlbums      = (conditions[1] != "");
    if(hasAlbums) sqlQuery += " JOIN albums a ON r.id_album = a.id_album";

    bool hasPerformers  = (conditions[2] != "");
    if(hasPerformers) sqlQuery += " JOIN performers p ON r.id_performer = p.id_performer";

    for(int i=0; i < conditions.size(); i++){
      if (sqlQuery.find("WHERE") == std::string::npos && conditions[i] != "") sqlQuery += " WHERE (" + conditions[i] + ")"; 
      else if (sqlQuery.find("WHERE") != std::string::npos && conditions[i] != "") sqlQuery += " AND (" + conditions[i] + ")"; 
    }

  } catch (const std::regex_error& e) {
    std::cerr << "Regex error: " << e.what() << std::endl;
    return "";
  }   
  return sqlQuery+";";
}
