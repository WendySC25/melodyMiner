#include "include/database/DatabaseUtils.h"
#include <iostream>

PerformerDAO::PerformerDAO(Database &db) : BaseDAO<Performer>(db, "performers") {}

void PerformerDAO::bindInsert(sqlite3_stmt *stmt, const Performer &performer) {
    sqlite3_bind_int(stmt, 1, performer.getIdType());
    sqlite3_bind_text(stmt, 2, performer.getName().c_str(), -1, SQLITE_TRANSIENT);
}

void PerformerDAO::bindUpdate(sqlite3_stmt *stmt, const Performer &performer) {
    sqlite3_bind_int(stmt, 1, performer.getIdType());
    sqlite3_bind_text(stmt, 2, performer.getName().c_str(), -1, SQLITE_STATIC);
}

void PerformerDAO::fillObject(sqlite3_stmt *stmt, Performer &performer) {
    performer.setIdPerformer(sqlite3_column_int(stmt, 0));
    performer.setIdType(sqlite3_column_int(stmt, 0));
    performer.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
}

std::string PerformerDAO::getInsertQuery() const {
    return "INSERT INTO performers (id_type, name) VALUES (?, ?);";
}

std::string PerformerDAO::getUpdateQuery() const {
    return "UPDATE albums SET id_type = ?, name = ? WHERE id_performer = ?;";
}

std::string PerformerDAO::getSelectByIdQuery() const {
    return "SELECT * FROM performers WHERE id_performer = ?;";
}