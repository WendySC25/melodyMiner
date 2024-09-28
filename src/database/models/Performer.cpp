#include "include/database/models/Performer.h"

Performer::Performer(int id_performer, int id_type, const std::string &name)
    : id_performer(id_performer), id_type(id_type), name(name) {}

int Performer::getIdPerformer() const {
    return id_performer;
}

int Performer::getIdType() const {
    return id_type;
}

std::string Performer::getName() const {
    return name;
}

void Performer::setIdPerformer(int id_performer) {
    this->id_performer = id_performer;
}

void Performer::setIdType(int id_type) {
    this->id_type = id_type;
}

void Performer::setName(const std::string &name) {
    this->name = name;
}
