#include "src/gui/MinerDialog.h"
#include "include/Miner.h"

MinerDialog::MinerDialog(Gtk::Window* parent, const std::string path) {

    auto builder    = Gtk::Builder::create_from_file("src/gui/minerDialog.ui");
    m_MainWindow    = builder->get_widget<Gtk::Window>("MinerDialog");
    m_PathLabel     = builder->get_widget<Gtk::Label>("path_label");
    m_ProgressBar   = builder->get_widget<Gtk::ProgressBar>("progress_bar");
    m_ButtonQuit    = builder->get_widget<Gtk::Button>("quit_button");

    m_MainWindow->set_transient_for(*parent);

   
    m_ButtonQuit->signal_clicked().connect(sigc::mem_fun(*this, &MinerDialog::on_quit_button_clicked));
    m_PathLabel->set_text("Mining on " + path);

    std::thread mining_thread(&MinerDialog::start_mining, this, path);
    mining_thread.detach(); 

    m_MainWindow->show();
}

void MinerDialog::start_mining(const std::string& path) {
    miner.findMusicFiles(path); 
    miner.mineTags([this](double progress) {
        std::cout << "Progreso: " << (progress * 100) << "%" << std::endl;
        update_progress(progress); 
    });

    std::cout << "Mining completed." << std::endl;
}

void MinerDialog::update_progress(double fraction) {
    m_ProgressBar->set_fraction(fraction);
    m_ProgressBar->set_text(std::to_string(static_cast<int>(fraction * 100)) + "%");
}

void MinerDialog::on_quit_button_clicked(){
    m_MainWindow->close();
    set_visible(false);
}