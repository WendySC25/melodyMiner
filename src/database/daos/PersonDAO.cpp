#include "include/database/DatabaseUtils.h"
#include <iostream>

PersonDAO::PersonDAO(Database &db) : BaseDAO<Person>(db, "persons") {}

void PersonDAO::bindInsert(sqlite3_stmt *stmt, const Person &person) {
    sqlite3_bind_text(stmt, 1, person.getStageName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, person.getRealName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, person.getBirthDate().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, person.getDeathDate().c_str(), -1, SQLITE_TRANSIENT);
}

void PersonDAO::bindUpdate(sqlite3_stmt *stmt, const Person &person) {
    sqlite3_bind_text(stmt, 1, person.getStageName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, person.getRealName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, person.getBirthDate().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, person.getDeathDate().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, person.getIdPerson());
}

void PersonDAO::fillObject(sqlite3_stmt *stmt, Person &person) {
    person.setIdPerson(sqlite3_column_int(stmt, 0));
    person.setStageName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    person.setRealName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    person.setBirthDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    person.setDeathDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
}

std::string PersonDAO::getInsertQuery() const {
    return "INSERT INTO persons (stage_name, real_name, birth_date, death_date) VALUES (?, ?, ?, ?);";
}

std::string PersonDAO::getUpdateQuery() const {
    return "UPDATE persons SET stage_name = ?, real_name = ?, birth_date = ?, death_date = ? WHERE id_person = ?;";
}

std::string PersonDAO::getSelectByIdQuery() const {
    return "SELECT * FROM persons WHERE id_person = ?;";
}


void PersonDAO::bindAttribute(sqlite3_stmt *stmt, std::string attributeValue)  {
   sqlite3_bind_text(stmt, 1, attributeValue.c_str(), -1, SQLITE_STATIC);
}

std::string PersonDAO::getSelectByAttibute() const {
    return "SELECT id_album FROM albums WHERE name = ?;";
}