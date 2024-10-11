#ifndef GROUPDAO_H
#define GROUPDAO_H

#include "include/database/DatabaseUtils.h"

class GroupDAO : public BaseDAO<Group> {
public:
    GroupDAO(Database &db);

protected:
    void bindInsert(sqlite3_stmt *stmt, const Group &group) override;
    void bindUpdate(sqlite3_stmt *stmt, const Group &group) override;
    void fillObject(sqlite3_stmt *stmt, Group &group) override;
    void bindAttribute(sqlite3_stmt *stmt, std::string attributeValue) override;

    std::string getInsertQuery() const override;
    std::string getUpdateQuery() const override;
    std::string getSelectByIdQuery() const override;
    std::string getSelectByAttibute() const override;
};

#endif

