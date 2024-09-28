#include "PerformerDAO.h"
#include <iostream>

PerformerDAO::PerformerDAO(Database &db) : database(db) {}

void PerformerDAO::addPerformer(const Performer &performer) {
    std::string sql = "INSERT INTO performers (id_type, name) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(database.getDb(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, performer.id_type);
        sqlite3_bind_text(stmt, 2, performer.name.c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error al insertar performer: " << sqlite3_errmsg(database.getDb()) << std::endl;
        }
    }
    sqlite3_finalize(stmt);
}

std::vector<Performer> PerformerDAO::getAllPerformers() {
    std::vector<Performer> performers;
    const char *sql = "SELECT id_performer, id_type, name FROM performers;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(database.getDb(), sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Performer performer;
            performer.id_performer = sqlite3_column_int(stmt, 0);
            performer.id_type = sqlite3_column_int(stmt, 1);
            performer.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            performers.push_back(performer);
        }
    } else {
        std::cerr << "Error al obtener performers: " << sqlite3_errmsg(database.getDb()) << std::endl;
    }
    sqlite3_finalize(stmt);
    return performers;
}
