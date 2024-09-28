#ifndef PERFORMER_DAO_H
#define PERFORMER_DAO_H

#include <string>
#include <vector>
#include "include/Database.h"  

class Performer {
public:
    int         id_performer;
    int         id_type;
    std::string name;
};

class PerformerDAO {
    public:
        PerformerDAO(Database &db);
        void addPerformer(const Performer &performer);
        std::vector<Performer> getAllPerformers();
        
    private:
        Database &database;
};

#endif // PERFORMER_DAO_H
