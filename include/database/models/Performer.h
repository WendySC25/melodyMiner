#ifndef PERFORMER_H
#define PERFORMER_H

#include <string>

/**
 * @class Performer
 * @brief Represents a performer with identification and name.
 */
class Performer {
public:
    /**
     * @brief Constructs a Performer object.
     * @param id_performer Unique identifier for the performer.
     * @param id_type Type of performer (e.g., artist, band).
     * @param name The name of the performer.
     */
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
