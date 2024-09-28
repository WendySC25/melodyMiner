#include "include/database/models/Person.h"

// Constructor
Person::Person(int id_person, const std::string &stage_name, 
               const std::string &real_name, const std::string &birth_date, 
               const std::string &death_date)
    : id_person(id_person), stage_name(stage_name), real_name(real_name), 
      birth_date(birth_date), death_date(death_date) {}

// Getters
int Person::getIdPerson() const { return id_person; }
std::string Person::getStageName() const { return stage_name; }
std::string Person::getRealName() const { return real_name; }
std::string Person::getBirthDate() const { return birth_date; }
std::string Person::getDeathDate() const { return death_date; }

// Setters
void Person::setIdPerson(int id_person) { this->id_person = id_person; }
void Person::setStageName(const std::string &stage_name) { this->stage_name = stage_name; }
void Person::setRealName(const std::string &real_name) { this->real_name = real_name; }
void Person::setBirthDate(const std::string &birth_date) { this->birth_date = birth_date; }
void Person::setDeathDate(const std::string &death_date) { this->death_date = death_date; }
