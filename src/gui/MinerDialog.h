#ifndef MINERDIALOG_H
#define MINERDIALOG_H

#include <gtkmm.h>
#include <thread>
#include <atomic>

#include "include/Miner.h"

class MinerDialog : public Gtk::Window
{
public:
  MinerDialog(const std::string& path, Database& db);
  void notify();

private:
  // Signal handlers.
  void on_start_button_clicked();
  void on_stop_button_clicked();
  void on_quit_button_clicked();
  void update_start_stop_buttons();
  void update_widgets();

  // Dispatcher handler.
  void on_notification_from_worker_thread();

  // Member data.
  Gtk::Box m_VBox;
  Gtk::Box m_ButtonBox;
  Gtk::Button m_ButtonStart;
  Gtk::Button m_ButtonStop;
  Gtk::Button m_ButtonQuit;
  Gtk::ProgressBar m_ProgressBar;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TextView m_TextView;

  Glib::Dispatcher m_Dispatcher;
  Miner m_Worker;
  std::string m_path;
  std::thread* m_WorkerThread;
};

#endif

