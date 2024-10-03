#include "include/database/DatabaseUtils.h"
#include <iostream>

RolaDAO::RolaDAO(Database &db) : BaseDAO<Rola>(db, "rolas") {}

void RolaDAO::bindInsert(sqlite3_stmt *stmt, const Rola &rola) {
    sqlite3_bind_int(stmt, 1, rola.getIdPerformer());
    sqlite3_bind_int(stmt, 2, rola.getIdAlbum());
    sqlite3_bind_text(stmt, 3, rola.getPath().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, rola.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, rola.getTrack());
    sqlite3_bind_int(stmt, 6, rola.getYear());
    sqlite3_bind_text(stmt, 7, rola.getGenre().c_str(), -1, SQLITE_TRANSIENT);
}

void RolaDAO::bindUpdate(sqlite3_stmt *stmt, const Rola &rola) {
    sqlite3_bind_int(stmt, 1, rola.getIdPerformer());
    sqlite3_bind_int(stmt, 2, rola.getIdAlbum());
    sqlite3_bind_text(stmt, 3, rola.getPath().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, rola.getTitle().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, rola.getTrack());
    sqlite3_bind_int(stmt, 6, rola.getYear());
    sqlite3_bind_text(stmt, 7, rola.getGenre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 8, rola.getIdRola());
}

void RolaDAO::fillObject(sqlite3_stmt *stmt, Rola &rola) {
    rola.setIdRola(sqlite3_column_int(stmt, 0));
    rola.setIdPerformer(sqlite3_column_int(stmt, 1));
    rola.setIdAlbum(sqlite3_column_int(stmt, 2));
    rola.setPath(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
    rola.setTitle(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
    rola.setTrack(sqlite3_column_int(stmt, 5));
    rola.setYear(sqlite3_column_int(stmt, 6));
    rola.setGenre(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
}

std::string RolaDAO::getInsertQuery() const {
    return "INSERT INTO rolas (id_performer, id_album, path, title, track, year, genre) VALUES (?, ?, ?, ?, ?, ?, ?);";
}

std::string RolaDAO::getUpdateQuery() const {
    return "UPDATE rolas SET id_performer = ?, id_album = ?, path = ?, title = ?, track = ?, year = ?, genre = ? WHERE id_rola = ?;";
}

std::string RolaDAO::getSelectByIdQuery() const {
    return "SELECT * FROM rolas WHERE id_rola = ?;";
}





void RolaDAO::bindAttribute(sqlite3_stmt *stmt, std::string attributeValue)  {
   sqlite3_bind_text(stmt, 1, attributeValue.c_str(), -1, SQLITE_STATIC);
}

std::string RolaDAO::getSelectByAttibute() const {
    return "SELECT id_album FROM albums WHERE name = ?;";
}
