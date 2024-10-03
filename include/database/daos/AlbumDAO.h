#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include "include/database/DatabaseUtils.h"

class AlbumDAO : public BaseDAO<Album> {
public:
    AlbumDAO(Database &db);
    int getIdByAttribute(const std::string &attributeValue) override;

protected:
    void bindInsert(sqlite3_stmt *stmt, const Album &album) override;
    void bindUpdate(sqlite3_stmt *stmt, const Album &album) override;
    void fillObject(sqlite3_stmt *stmt, Album &album) override;
    void bindAttribute(sqlite3_stmt *stmt, std::string attributeValue) override;

    std::string getInsertQuery() const override;
    std::string getUpdateQuery() const override;
    std::string getSelectByIdQuery() const override;
    std::string getSelectByAttibute() const override;
};

#endif // ALBUMDAO_H

