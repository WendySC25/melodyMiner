#ifndef MINERDIALOG_H
#define MINERDIALOG_H

#include <gtkmm.h>

#include <thread>
#include <atomic>
#include "include/Miner.h"

class MinerDialog : public Gtk::Window {
public:
    MinerDialog(Gtk::Window*  parent, const std::string path);
    void update_progress(double fraction);

private:
    Gtk::Window* m_MainWindow;
    Gtk::Label* m_PathLabel;
    Gtk::ProgressBar* m_ProgressBar;
    std::atomic<bool> m_cancel; 

    std::thread m_WorkerThread;
    Miner miner;
    std::mutex miner_mutex;
    Glib::Dispatcher m_Dispatcher;
    

    Gtk::Button* m_ButtonQuit;

    double m_progress_value = 0;

    void start_mining(const std::string& path);
    void on_quit_button_clicked();
};

#endif

