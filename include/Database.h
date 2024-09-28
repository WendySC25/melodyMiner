#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>

class Database {
public:
    Database(const std::string &db_name);
    ~Database();
    void createTables();
    sqlite3* getDb() { return db; }

private:
    sqlite3 *db;  
    void executeSQL(const std::string &sql);
};

#endif // DATABASE_H
