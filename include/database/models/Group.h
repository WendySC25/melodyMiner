#ifndef GROUP_H
#define GROUP_H

#include <string>

/**
 * @class Group
 * @brief Represents a musical group with identification and dates.
 */
class Group {
public:
    /**
     * @brief Constructs a Group object.
     * @param id_group Unique identifier for the group.
     * @param name The name of the group.
     * @param start_date The start date of the group's activity.
     * @param end_date The end date of the group's activity.
     */
    Group(int id_group = 0, const std::string &name = "", 
          const std::string &start_date = "", const std::string &end_date = "");

    int getIdGroup() const;
    std::string getName() const;
    std::string getStartDate() const;
    std::string getEndDate() const;

    void setIdGroup(int id_group);
    void setName(const std::string &name);
    void setStartDate(const std::string &start_date);
    void setEndDate(const std::string &end_date);

private:
    int id_group;
    std::string name;
    std::string start_date;
    std::string end_date;
};

#endif // GROUP_H
