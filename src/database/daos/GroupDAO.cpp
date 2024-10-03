#include "include/database/DatabaseUtils.h"
#include <iostream>

GroupDAO::GroupDAO(Database &db) : BaseDAO<Group>(db, "groups") {}

void GroupDAO::bindInsert(sqlite3_stmt *stmt, const Group &group) {
    sqlite3_bind_text(stmt, 1, group.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, group.getStartDate().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, group.getEndDate().c_str(), -1, SQLITE_TRANSIENT);
}

void GroupDAO::bindUpdate(sqlite3_stmt *stmt, const Group &group) {
    sqlite3_bind_text(stmt, 1, group.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, group.getStartDate().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, group.getEndDate().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, group.getIdGroup());
}

void GroupDAO::fillObject(sqlite3_stmt *stmt, Group &group) {
    group.setIdGroup(sqlite3_column_int(stmt, 0));
    group.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    group.setStartDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    group.setEndDate(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
}

std::string GroupDAO::getInsertQuery() const {
    return "INSERT INTO groups (name, start_date, end_date) VALUES (?, ?, ?);";
}

std::string GroupDAO::getUpdateQuery() const {
    return "UPDATE groups SET name = ?, start_date = ?, end_date = ? WHERE id_group = ?;";
}

std::string GroupDAO::getSelectByIdQuery() const {
    return "SELECT * FROM groups WHERE id_group = ?;";
}




void GroupDAO::bindAttribute(sqlite3_stmt *stmt, std::string attributeValue)  {
   sqlite3_bind_text(stmt, 1, attributeValue.c_str(), -1, SQLITE_STATIC);
}

std::string GroupDAO::getSelectByAttibute() const {
    return "SELECT id_album FROM albums WHERE name = ?;";
}