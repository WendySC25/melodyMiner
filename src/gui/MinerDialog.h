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
    Gtk::Button* m_ButtonQuit;

    Miner miner;

    void start_mining(const std::string& path);
    void on_quit_button_clicked();
};

#endif

