#ifndef MINER_H
#define MINER_H

#include <gtkmm.h>

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>

#include "include/ID3TagManager.h"

class MinerDialog;


class Miner {
public:
    Miner(Database &db);

    void mineTags(MinerDialog* caller, std::string directory);
    void findMusicFiles(const std::string& directory);

    void get_data(double* fraction_done, Glib::ustring* message) const;
    void stop_work();
    bool has_stopped() const;

private:
    mutable std::mutex m_Mutex;
    bool m_shall_stop;
    bool m_has_stopped;
    double m_fraction_done;
    std::vector<std::string> file_paths;
    Glib::ustring m_message;
    ID3TagManager tagManager;
};

#endif // MINER_H


