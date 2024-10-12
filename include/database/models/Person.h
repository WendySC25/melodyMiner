#ifndef PERSON_H
#define PERSON_H

#include <string>

/**
 * @class Person
 * @brief Represents a person with personal and stage information.
 */
class Person {
public:
    /**
     * @brief Constructs a Person object.
     * @param id_person Unique identifier for the person.
     * @param stage_name The stage name of the person.
     * @param real_name The real name of the person.
     * @param birth_date The birth date of the person.
     * @param death_date The death date of the person (if applicable).
     */
    Person(int id_person = 0, const std::string &stage_name = "", 
           const std::string &real_name = "", const std::string &birth_date = "", 
           const std::string &death_date = "");

    int getIdPerson() const;
    std::string getStageName() const;
    std::string getRealName() const;
    std::string getBirthDate() const;
    std::string getDeathDate() const;

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
