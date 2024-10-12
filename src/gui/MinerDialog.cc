#include "src/gui/MinerDialog.h"

MinerDialog::MinerDialog(const std::string& path, Database& db) :
  m_VBox(Gtk::Orientation::VERTICAL, 5),
  m_ButtonBox(Gtk::Orientation::HORIZONTAL),
  m_ButtonStart("Start work"),
  m_ButtonStop("Stop work"),
  m_ButtonQuit("_Quit", /* mnemonic= */ true),
  m_ProgressBar(),
  m_ScrolledWindow(),
  m_TextView(),
  m_Dispatcher(),
  m_Worker(db),
  m_path(path),
  m_WorkerThread(nullptr)
  
{
  set_title("Mining");
  set_default_size(300, 300);

  m_VBox.set_margin(5);
  set_child(m_VBox);

  m_VBox.append(m_ProgressBar);
  m_ProgressBar.set_text("Fraction done");
  m_ProgressBar.set_show_text();
  m_ProgressBar.set_size_request(250, 30);
  m_ScrolledWindow.set_child(m_TextView);
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);
  m_TextView.set_editable(false);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_ButtonStart);
  m_ButtonBox.append(m_ButtonStop);
  m_ButtonBox.append(m_ButtonQuit);
  m_ButtonBox.set_margin(5);
  m_ButtonBox.set_spacing(5);
  m_ButtonStart.set_hexpand(true);
  m_ButtonStart.set_halign(Gtk::Align::END);

  m_ButtonStart.signal_clicked().connect(sigc::mem_fun(*this, &MinerDialog::on_start_button_clicked));
  m_ButtonStop.signal_clicked().connect(sigc::mem_fun(*this, &MinerDialog::on_stop_button_clicked));
  m_ButtonQuit.signal_clicked().connect(sigc::mem_fun(*this, &MinerDialog::on_quit_button_clicked));
  m_Dispatcher.connect(sigc::mem_fun(*this, &MinerDialog::on_notification_from_worker_thread));

  auto buffer = m_TextView.get_buffer();
  buffer->create_mark("last_line", buffer->end(), /* left_gravity= */ true);

  update_start_stop_buttons();
  show();
}

void MinerDialog::on_start_button_clicked(){
  if (m_WorkerThread) std::cout << "Can't start a worker thread while another one is running." << std::endl;
  else m_WorkerThread = new std::thread([this] {  m_Worker.mineTags(this, m_path); });
  update_start_stop_buttons();
}

void MinerDialog::on_stop_button_clicked(){
  if (!m_WorkerThread) std::cout << "Can't stop a worker thread. None is running." << std::endl;
  else{
    m_Worker.stop_work();
    m_ButtonStop.set_sensitive(false);
  }
}

void MinerDialog::update_start_stop_buttons(){
  const bool thread_is_running = m_WorkerThread != nullptr;
  m_ButtonStart.set_sensitive(!thread_is_running);
  m_ButtonStop.set_sensitive(thread_is_running);
}

void MinerDialog::update_widgets(){
  double fraction_done;
  Glib::ustring message_from_worker_thread;
  m_Worker.get_data(&fraction_done, &message_from_worker_thread);
  m_ProgressBar.set_fraction(fraction_done);

  if (message_from_worker_thread != m_TextView.get_buffer()->get_text()){
    auto buffer = m_TextView.get_buffer();
    buffer->set_text(message_from_worker_thread);
    auto iter = buffer->end();
    iter.set_line_offset(0); 
    auto mark = buffer->get_mark("last_line");
    buffer->move_mark(mark, iter);
    m_TextView.scroll_to(mark);
  }
}

void MinerDialog::on_quit_button_clicked(){
  if (m_WorkerThread){
    m_Worker.stop_work();
    if (m_WorkerThread->joinable()) m_WorkerThread->join();
  }

  set_visible(false);
}

void MinerDialog::notify(){
  m_Dispatcher.emit();
}

void MinerDialog::on_notification_from_worker_thread(){
  if (m_WorkerThread && m_Worker.has_stopped()){
    if (m_WorkerThread->joinable()) m_WorkerThread->join();
    delete m_WorkerThread;
    m_WorkerThread = nullptr;
    update_start_stop_buttons();
  }
  update_widgets();
}
