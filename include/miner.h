#ifndef MINER_H
#define MINER_H

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <taglib/tag_c.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include "ID3Tag.h"
#include "include/ID3TagManager.h"

class Miner {
public:
    Miner();

    void findMusicFiles(const std::string& directory);
    void mineTags(const std::function<void(double)>& progressCallback);
    void stopMining();

    double getProgress() const;
    bool isStopped() const;

private:
    mutable std::mutex m_Mutex; // Para sincronizar el acceso a datos compartidos
    std::vector<std::string> file_paths;
    bool m_shall_stop; // Indica si debe detenerse
    bool m_has_stopped; // Indica si ya se detuvo
    double m_fraction_done; // Progreso actual
};

#endif // MINER_H

