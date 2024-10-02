#include "include/database/daos/AlbumDAO.h"
#include "include/database/models/Album.h"
#include <iostream>

AlbumDAO::AlbumDAO(Database &db) : BaseDAO<Album>(db, "albums") {}

void AlbumDAO::bindInsert(sqlite3_stmt *stmt, const Album &album) {
    std::cout << "Valores antes de bindInsert: "
          << album.getPath() << ", "
          << album.getName() << ", "
          << album.getYear() << std::endl;

    sqlite3_bind_text(stmt, 1, album.getPath().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, album.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, album.getYear());

    std::cout << "Insertando Album: " << album.getPath() << ", " << album.getName() << ", " << album.getYear() << std::endl;

}

void AlbumDAO::bindUpdate(sqlite3_stmt *stmt, const Album &album) {
    sqlite3_bind_text(stmt, 1, album.getPath().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, album.getName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, album.getYear());
    sqlite3_bind_int(stmt, 4, album.getIdAlbum());
}

void AlbumDAO::fillObject(sqlite3_stmt *stmt, Album &album) {
    album.setIdAlbum(sqlite3_column_int(stmt, 0));
    album.setPath(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    album.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    album.setYear(sqlite3_column_int(stmt, 3));
}

std::string AlbumDAO::getInsertQuery() const {
    return "INSERT INTO albums (path, name, year) VALUES (?, ?, ?);";
}

std::string AlbumDAO::getUpdateQuery() const {
    return "UPDATE albums SET path = ?, name = ?, year = ? WHERE id_album = ?;";
}

std::string AlbumDAO::getSelectByIdQuery() const {
    return "SELECT * FROM albums WHERE id_album = ?;";
}