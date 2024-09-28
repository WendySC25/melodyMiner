#ifndef PERFORMER_H
#define PERFORMER_H

#include <string>

class Performer {
public:
    Performer(int id_performer = 0, int id_type = 0, const std::string &name = "");

    int getIdPerformer() const;
    int getIdType() const;
    std::string getName() const;

    void setIdPerformer(int id_performer);
    void setIdType(int id_type);
    void setName(const std::string &name);

private:
    int id_performer;
    int id_type;
    std::string name;
};

#endif // PERFORMER_H
