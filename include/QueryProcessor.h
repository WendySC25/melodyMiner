#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <sstream>

/**
 * @class QueryProcessor
 * @brief Processes queries to generate SQL statements.
 */
class QueryProcessor {
public:
  /**
   * @brief Constructs a QueryProcessor object.
   */
  QueryProcessor();

  /**
   * @brief Processes a given query string to generate an SQL query.
   * @param query The input query string.
   * @return The generated SQL query as a string.
   */
  std::string processQuery(const std::string& query);

private:
  /**
   * @brief Joins a vector of strings with a specified delimiter.
   * @param vec The vector of strings to join.
   * @param delim The delimiter string.
   * @return The joined string.
   */
  std::string join(const std::vector<std::string>& vec, const std::string& delim);

  /**
   * @brief Generates a regex pattern for a specific field.
   * @param field The field name.
   * @return The generated regex pattern.
   */
  std::regex getPattern(const std::string& field);

  /**
   * @brief Extracts conditions from a query for a specific field.
   * @param field The field name.
   * @param query The input query string.
   * @param con The base condition string.
   * @param isString Flag indicating if the condition is for a string type.
   * @return The extracted condition as a string.
   */
  std::string getCondition(const std::string& field, const std::string& query, const std::string& con, bool isString);
};

#endif
