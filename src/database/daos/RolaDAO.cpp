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

    AlbumDAO albumDAO(database);
    Album album = albumDAO.getById(sqlite3_column_int(stmt, 2));
    std::shared_ptr<Album> albumPtr = std::make_shared<Album>(album);
    rola.setAlbum(albumPtr);

    PerformerDAO performerDAO(database);
    Performer perfomer = performerDAO.getById(sqlite3_column_int(stmt, 1));
    std::shared_ptr<Performer> performerPtr = std::make_shared<Performer>(perfomer);
    rola.setPerformer(performerPtr);
    
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
    return "SELECT id_rola FROM rolas WHERE title = ?;";
}

int RolaDAO::getIdByAttribute(const std::string &attributeValue) {
    return BaseDAO<Rola>::getIdByAttribute(attributeValue);
}


std::vector<Rola> RolaDAO::executeQuery(const std::string& input) {
    QueryProcessor queryProcessor;
    std::string query = queryProcessor.processQuery(input);

    std::vector<Rola> rolas;
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(database.getDb(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Rola rola;
            fillObject(stmt, rola); 
            rolas.push_back(rola);  
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(database.getDb()) << std::endl;
    }
    return rolas; 
}
