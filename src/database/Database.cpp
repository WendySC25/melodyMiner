#include "include/Database.h"
#include <iostream>

Database::Database(const std::string &db_name) {
   
    int rc = sqlite3_open(db_name.c_str(), &db);
    if (rc) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::createTables() {

    const char *sql_types = R"(
        CREATE TABLE IF NOT EXISTS types (
            id_type INTEGER PRIMARY KEY,
            description TEXT
        );
    )";

    const char *sql_insert_types = R"(
        INSERT INTO types (id_type, description) VALUES
        (0, 'Person'),
        (1, 'Group'),
        (2, 'Unknown');
    )";

    const char *sql_performers = R"(
        CREATE TABLE IF NOT EXISTS performers (
            id_performer INTEGER PRIMARY KEY,
            id_type INTEGER,
            name TEXT,
            FOREIGN KEY (id_type) REFERENCES types(id_type)
        );
    )";

    const char *sql_persons = R"(
        CREATE TABLE IF NOT EXISTS persons (
            id_person INTEGER PRIMARY KEY,
            stage_name TEXT,
            real_name TEXT,
            birth_date TEXT,
            death_date TEXT
        );
    )";

    const char *sql_groups = R"(
        CREATE TABLE IF NOT EXISTS groups (
            id_group INTEGER PRIMARY KEY,
            name TEXT,
            start_date TEXT,
            end_date TEXT
        );
    )";

    const char *sql_in_group = R"(
        CREATE TABLE IF NOT EXISTS in_group (
            id_person INTEGER,
            id_group INTEGER,
            PRIMARY KEY (id_person, id_group),
            FOREIGN KEY (id_person) REFERENCES persons(id_person),
            FOREIGN KEY (id_group) REFERENCES groups(id_group)
        );
    )";

    const char *sql_albums = R"(
        CREATE TABLE IF NOT EXISTS albums (
            id_album INTEGER PRIMARY KEY,
            path TEXT,
            name TEXT,
            year INTEGER
        );
    )";

    const char *sql_rolas = R"(
        CREATE TABLE IF NOT EXISTS rolas (
            id_rola INTEGER PRIMARY KEY,
            id_performer INTEGER,
            id_album INTEGER,
            path TEXT,
            title TEXT,
            track INTEGER,
            year INTEGER,
            genre TEXT,
            FOREIGN KEY (id_performer) REFERENCES performers(id_performer),
            FOREIGN KEY (id_album) REFERENCES albums(id_album)
        );
    )";

    executeSQL(sql_types);
    executeSQL(sql_insert_types);
    executeSQL(sql_performers);
    executeSQL(sql_persons);
    executeSQL(sql_groups);
    executeSQL(sql_in_group);
    executeSQL(sql_albums);
    executeSQL(sql_rolas);
}

void Database::executeSQL(const std::string &sql) {
    char *error_message = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &error_message);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error al ejecutar SQL: " << error_message << std::endl;
        sqlite3_free(error_message);
    }
}
