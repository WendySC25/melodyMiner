#ifndef GROUP_H
#define GROUP_H

#include <string>

class Group {
public:
    Group(int id_group = 0, const std::string &name = "", 
          const std::string &start_date = "", const std::string &end_date = "");

    // Getters
    int getIdGroup() const;
    std::string getName() const;
    std::string getStartDate() const;
    std::string getEndDate() const;

    // Setters
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
