#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include "include/database/models/Album.h"
#include "include/database/daos/BaseDAO.h"
#include "include/Database.h"

class AlbumDAO : public BaseDAO<Album> {
public:
    AlbumDAO(Database &db);

protected:
    void bindInsert(sqlite3_stmt *stmt, const Album &album) override;
    void bindUpdate(sqlite3_stmt *stmt, const Album &album) override;
    void fillObject(sqlite3_stmt *stmt, Album &album) override;

    std::string getInsertQuery() const override;
    std::string getUpdateQuery() const override;
    std::string getSelectByIdQuery() const override;
};

#endif // ALBUMDAO_H

