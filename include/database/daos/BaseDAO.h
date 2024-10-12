#ifndef BASEDAO_H
#define BASEDAO_H

#include "include/Database.h"
#include <vector>
#include <string>
#include <sqlite3.h>
#include <iostream>

/**
 * @brief A generic base Data Access Object (DAO) class for managing database operations.
 * @tparam T The type of the object that this DAO will handle.
 */
template <typename T>
class BaseDAO {
public:
  BaseDAO(Database &db, const std::string &tableName) 
    : database(db), tableName(tableName) {}

  /**
   * @brief Adds a new item to the database.
   * @param item The item to add.
   * @return The ID of the newly added item.
   */
  int add(const T &item);

  /**
   * @brief Retrieves all items from the database.
   * @return A vector of items.
   */
  std::vector<T> getAll();

  /**
   * @brief Retrieves an item by its ID.
   * @param id The ID of the item.
   * @return The item with the specified ID.
   */
  T getById(int id);

  /**
   * @brief Updates an existing item in the database.
   * @param item The item to update.
   */
  void update(const T &item);

  /**
   * @brief Removes an item from the database by its ID.
   * @param id The ID of the item to remove.
   */
  void remove(int id);

  /**
   * @brief Retrieves the ID of an item by a specific attribute.
   * @param attributeValue The value of the attribute to search for.
   * @return The ID of the item, or -1 if not found.
   */
  virtual int getIdByAttribute(const std::string &attributeValue) = 0;

protected:
  virtual void bindInsert(sqlite3_stmt *stmt, const T &item) = 0;
  virtual void bindUpdate(sqlite3_stmt *stmt, const T &item) = 0;
  virtual void fillObject(sqlite3_stmt *stmt, T &item) = 0;
  virtual void bindAttribute(sqlite3_stmt *stmt, std::string attributeValue) = 0;

  virtual std::string getInsertQuery() const = 0;
  virtual std::string getUpdateQuery() const = 0;
  virtual std::string getSelectByIdQuery() const = 0;
  virtual std::string getSelectByAttibute() const = 0;
        

  Database &database;
  std::string tableName;
};


template <typename T>
int BaseDAO<T>::add(const T &item) {

  std::string sql = getInsertQuery();
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(database.getDb(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(database.getDb()) << std::endl;
    return -1;
  }

  bindInsert(stmt, item);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    std::cerr << "Error al insertar: " << sqlite3_errmsg(database.getDb()) << std::endl;
    return -1;
  }
    
  int lastInsertId = static_cast<int>(sqlite3_last_insert_rowid(database.getDb()));
  sqlite3_finalize(stmt);
  return lastInsertId; 

}

template <typename T>
std::vector<T> BaseDAO<T>::getAll() {
  std::vector<T> items;
  std::string sql = "SELECT * FROM " + tableName + ";";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(database.getDb(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(database.getDb()) << std::endl;
    return items;
  }

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    T item;
    fillObject(stmt, item);
    items.push_back(item);
  }

  sqlite3_finalize(stmt);
  return items;
}

template <typename T>
T BaseDAO<T>::getById(int id) {
  T item;
  std::string sql = getSelectByIdQuery();
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(database.getDb(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(database.getDb()) << std::endl;
    return item;
  }

  sqlite3_bind_int(stmt, 1, id);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    fillObject(stmt, item);
  } else {
    std::cerr << "Elemento no encontrado con ID: " << id << std::endl;
  }

  sqlite3_finalize(stmt);
  return item;
}

template <typename T>
void BaseDAO<T>::update(const T &item) {
  std::string sql = getUpdateQuery(); 
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(database.getDb(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(database.getDb()) << std::endl;
    return;
  }

  bindUpdate(stmt, item);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    std::cerr << "Error al actualizar: " << sqlite3_errmsg(database.getDb()) << std::endl;
  }

  sqlite3_finalize(stmt);
}

template <typename T>
void BaseDAO<T>::remove(int id) {
  std::string sql = "DELETE FROM " + tableName + " WHERE id = ?;";
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(database.getDb(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(database.getDb()) << std::endl;
    return;
  }

  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_DONE) 
    std::cerr << "Error al eliminar: " << sqlite3_errmsg(database.getDb()) << std::endl;
    
  sqlite3_finalize(stmt);
}

template <typename T>
int BaseDAO<T>::getIdByAttribute(const std::string &attributeValue) {
  std::string sql = getSelectByAttibute();
  sqlite3_stmt *stmt;

  if (sqlite3_prepare_v2(database.getDb(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(database.getDb()) << std::endl;
    return -1; 
  }

  bindAttribute(stmt, attributeValue);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0); 
    sqlite3_finalize(stmt);
    return id;
  }

  sqlite3_finalize(stmt);
  return -1;
}



#endif // BASEDAO_H

