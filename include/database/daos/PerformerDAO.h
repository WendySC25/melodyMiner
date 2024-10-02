#ifndef PERFORMERDAO_H
#define PERFORMERDAO_H

#include "include/database/DatabaseUtils.h"

class PerformerDAO : public BaseDAO<Performer> {
public:
    PerformerDAO(Database &db);

protected:
    void bindInsert(sqlite3_stmt *stmt, const Performer &performer) override;
    void bindUpdate(sqlite3_stmt *stmt, const Performer &performer) override;
    void fillObject(sqlite3_stmt *stmt, Performer &performer) override;

    std::string getInsertQuery() const override;
    std::string getUpdateQuery() const override;
    std::string getSelectByIdQuery() const override;
};

#endif // ALBUMDAO_H

