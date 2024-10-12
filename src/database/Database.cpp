#include "include/Database.h"
#include <iostream>

Database::Database(const std::string &dbPath) {
    if (!openDatabase(dbPath)) 
        std::cerr << "No se pudo abrir la base de datos: " << dbPath << std::endl;
    else createTables(); 
}

Database::~Database() {
    closeDatabase();
}

bool Database::openDatabase(const std::string &dbPath) {
    return sqlite3_open(dbPath.c_str(), &db) == SQLITE_OK;
}

void Database::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

sqlite3* Database::getDb() const {
    return db;
}

void Database::createTables() {
    const char* sql[] = {
        "CREATE TABLE IF NOT EXISTS types ("
        "id_type INTEGER PRIMARY KEY,"
        "description TEXT);",

        // "INSERT INTO types (id_type, description) VALUES (0, 'Person');",
        // "INSERT INTO types (id_type, description) VALUES (1, 'Group');",
        // "INSERT INTO types (id_type, description) VALUES (2, 'Unknown');",

        "CREATE TABLE IF NOT EXISTS performers ("
        "id_performer INTEGER PRIMARY KEY,"
        "id_type INTEGER,"
        "name TEXT,"
        "FOREIGN KEY (id_type) REFERENCES types(id_type));",

        "CREATE TABLE IF NOT EXISTS persons ("
        "id_person INTEGER PRIMARY KEY,"
        "stage_name TEXT,"
        "real_name TEXT,"
        "birth_date TEXT,"
        "death_date TEXT);",

        "CREATE TABLE IF NOT EXISTS groups ("
        "id_group INTEGER PRIMARY KEY,"
        "name TEXT,"
        "start_date TEXT,"
        "end_date TEXT);",

        "CREATE TABLE IF NOT EXISTS in_group ("
        "id_person INTEGER,"
        "id_group INTEGER,"
        "PRIMARY KEY (id_person, id_group),"
        "FOREIGN KEY (id_person) REFERENCES persons(id_person),"
        "FOREIGN KEY (id_group) REFERENCES groups(id_group));",

        "CREATE TABLE IF NOT EXISTS albums ("
        "id_album INTEGER PRIMARY KEY,"
        "path TEXT,"
        "name TEXT,"
        "year INTEGER);",

        "CREATE TABLE IF NOT EXISTS rolas ("
        "id_rola INTEGER PRIMARY KEY,"
        "id_performer INTEGER,"
        "id_album INTEGER,"
        "path TEXT,"
        "title TEXT,"
        "track INTEGER,"
        "year INTEGER,"
        "genre TEXT,"
        "FOREIGN KEY (id_performer) REFERENCES performers(id_performer),"
        "FOREIGN KEY (id_album) REFERENCES albums(id_album));"
    };

    for (const char* statement : sql) {
        char* errorMessage;
        if (sqlite3_exec(db, statement, 0, 0, &errorMessage) != SQLITE_OK) {
            std::cerr << "Error al ejecutar SQL: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
        }
    }
}
