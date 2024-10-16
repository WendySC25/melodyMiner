#ifndef ROLADAO_H
#define ROLADAO_H

#include "include/database/DatabaseUtils.h"

class RolaDAO : public BaseDAO<Rola> {
    public:
        RolaDAO(Database &db);
        int getIdByAttribute(const std::string &attributeValue) override;
        std::vector<Rola> executeQuery(const std::string& query);


    protected:
        void bindInsert(sqlite3_stmt *stmt, const Rola &rola) override;
        void bindUpdate(sqlite3_stmt *stmt, const Rola &rola) override;
        void fillObject(sqlite3_stmt *stmt, Rola &rola) override;
        void bindAttribute(sqlite3_stmt *stmt, std::string attributeValue) override;

        std::string getInsertQuery() const override;
        std::string getUpdateQuery() const override;
        std::string getSelectByIdQuery() const override;
        std::string getSelectByAttibute() const override;
};

#endif 

