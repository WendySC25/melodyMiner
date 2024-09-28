#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
public:
    Person(int id_person = 0, const std::string &stage_name = "", 
           const std::string &real_name = "", const std::string &birth_date = "", 
           const std::string &death_date = "");

    // Getters
    int getIdPerson() const;
    std::string getStageName() const;
    std::string getRealName() const;
    std::string getBirthDate() const;
    std::string getDeathDate() const;

    // Setters
    void setIdPerson(int id_person);
    void setStageName(const std::string &stage_name);
    void setRealName(const std::string &real_name);
    void setBirthDate(const std::string &birth_date);
    void setDeathDate(const std::string &death_date);

private:
    int id_person;
    std::string stage_name;
    std::string real_name;
    std::string birth_date;
    std::string death_date;
};

#endif // PERSON_H
