#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include "include/database/DatabaseUtils.h"

/**
 * @brief Data Access Object (DAO) for managing Album records in the database.
 */
class AlbumDAO : public BaseDAO<Album> {
public:
    /**
     * @brief Constructs an AlbumDAO object.
     * @param db Reference to the Database object.
     */
    AlbumDAO(Database &db);

    /**
     * @brief Retrieves the ID of an Album by a specific attribute.
     * @param attributeValue The value of the attribute to search for.
     * @return The ID of the Album, or -1 if not found.
     */
    int getIdByAttribute(const std::string &attributeValue) override;

protected:
    /**
     * @brief Binds the attributes of an Album to an insert statement.
     * @param stmt The prepared SQLite statement.
     * @param album The Album object whose attributes are to be bound.
     */
    void bindInsert(sqlite3_stmt *stmt, const Album &album) override;

    /**
     * @brief Binds the attributes of an Album to an update statement.
     * @param stmt The prepared SQLite statement.
     * @param album The Album object whose attributes are to be bound.
     */
    void bindUpdate(sqlite3_stmt *stmt, const Album &album) override;

    /**
     * @brief Fills an Album object with data from a SQLite statement.
     * @param stmt The SQLite statement containing the data.
     * @param album The Album object to fill with data.
     */
    void fillObject(sqlite3_stmt *stmt, Album &album) override;

    /**
     * @brief Binds an attribute value to a statement for searching.
     * @param stmt The prepared SQLite statement.
     * @param attributeValue The value of the attribute to bind.
     */
    void bindAttribute(sqlite3_stmt *stmt, std::string attributeValue) override;

    /**
     * @brief Gets the SQL query for inserting an Album.
     * @return The insert query as a string.
     */
    std::string getInsertQuery() const override;

    /**
     * @brief Gets the SQL query for updating an Album.
     * @return The update query as a string.
     */
    std::string getUpdateQuery() const override;

    /**
     * @brief Gets the SQL query for selecting an Album by ID.
     * @return The select query as a string.
     */
    std::string getSelectByIdQuery() const override;

    /**
     * @brief Gets the SQL query for selecting an Album by attribute.
     * @return The select query as a string.
     */
    std::string getSelectByAttibute() const override;
};

#endif // ALBUMDAO_H
