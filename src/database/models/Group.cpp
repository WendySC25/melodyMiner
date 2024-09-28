#include "Group.h"

// Constructor
Group::Group(int id_group, const std::string &name, 
             const std::string &start_date, const std::string &end_date)
    : id_group(id_group), name(name), start_date(start_date), end_date(end_date) {}

// Getters
int Group::getIdGroup() const { return id_group; }
std::string Group::getName() const { return name; }
std::string Group::getStartDate() const { return start_date; }
std::string Group::getEndDate() const { return end_date; }

// Setters
void Group::setIdGroup(int id_group) { this->id_group = id_group; }
void Group::setName(const std::string &name) { this->name = name; }
void Group::setStartDate(const std::string &start_date) { this->start_date = start_date; }
void Group::setEndDate(const std::string &end_date) { this->end_date = end_date; }
