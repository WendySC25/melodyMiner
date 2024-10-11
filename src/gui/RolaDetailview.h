#ifndef ROLADETAILWINDOW_H
#define ROLADETAILWINDOW_H

#include <gtkmm.h>
#include "include/database/models/Rola.h" 

class RolaDetailWindow : public Gtk::Window {
public:
    RolaDetailWindow(const Rola& rola);
    
private:
    Gtk::Window* m_MainWindow;
    Gtk::Label* m_TitleLabel;
    Gtk::Label* m_AlbumLabel;
    Gtk::Label* m_PerformerLabel;
    Gtk::Button* m_EditButton;
    Gtk::Button* m_DeleteButton;
    Gtk::Button* m_CancelButton;
};

#endif // ROLADETAILWINDOW_H
