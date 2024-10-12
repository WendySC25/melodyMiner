#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

/**
 * @class Database
 * @brief Manages a SQLite database connection.
 */
class Database {
public:
  /**
   * @brief Constructs a Database object and opens the connection.
   * @param dbPath Path to the database file.
   */
  Database(const std::string &dbPath);

  /**
   * @brief Closes the database connection.
   */
  ~Database();

  /**
   * @brief Retrieves the SQLite database pointer.
   * @return Pointer to the SQLite database.
   */
  sqlite3* getDb() const;

  /**
   * @brief Creates necessary tables in the database.
   */
  void createTables();

private:
  sqlite3 *db; ///< Pointer to the SQLite database.
    
  /**
   * @brief Opens a connection to the database.
   * @param dbPath Path to the database file.
   * @return True if successful, false otherwise.
   */
  bool openDatabase(const std::string &dbPath);

  /**
   * @brief Closes the database connection.
   */
  void closeDatabase();
};

#endif // DATABASE_H
