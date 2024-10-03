#ifndef PERSONDAO_H
#define PERSONDAO_H

#include "include/database/DatabaseUtils.h"

class PersonDAO : public BaseDAO<Person> {
public:
    PersonDAO(Database &db);

protected:
    void bindInsert(sqlite3_stmt *stmt, const Person &person) override;
    void bindUpdate(sqlite3_stmt *stmt, const Person &person) override;
    void fillObject(sqlite3_stmt *stmt, Person &person) override;
    void bindAttribute(sqlite3_stmt *stmt, std::string attributeValue) override;

    std::string getInsertQuery() const override;
    std::string getUpdateQuery() const override;
    std::string getSelectByIdQuery() const override;
    std::string getSelectByAttibute() const override;
};

#endif // ALBUMDAO_H

