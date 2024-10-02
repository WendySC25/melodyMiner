#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
public:
    Database(const std::string &dbPath);
    ~Database();

    sqlite3* getDb() const;
    void createTables();

private:
    sqlite3 *db;
    bool openDatabase(const std::string &dbPath);
    void closeDatabase();
};

#endif // DATABASE_H
