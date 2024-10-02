#ifndef ROLADAO_H
#define ROLADAO_H

#include "include/database/DatabaseUtils.h"

class RolaDAO : public BaseDAO<Rola> {
public:
    RolaDAO(Database &db);

protected:
    void bindInsert(sqlite3_stmt *stmt, const Rola &rola) override;
    void bindUpdate(sqlite3_stmt *stmt, const Rola &rola) override;
    void fillObject(sqlite3_stmt *stmt, Rola &rola) override;

    std::string getInsertQuery() const override;
    std::string getUpdateQuery() const override;
    std::string getSelectByIdQuery() const override;
};

#endif 

