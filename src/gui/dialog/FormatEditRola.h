#ifndef FORMATEDITROLA_H
#define FORMATEDITROLA_H

#include <gtkmm.h>
#include "include/database/models/Rola.h"

class FormatEditRola : public Gtk::Dialog {
public:
    FormatEditRola();
    void set_initial_data(const Rola& rola);
    
    std::string get_title() const;
    int get_track() const;
    int get_year() const;
    std::string get_genre() const;

private:
    Gtk::Entry m_TitleEntry;
    Gtk::Entry m_TrackEntry;
    Gtk::Entry m_YearEntry;
    Gtk::Entry m_GenreEntry;

    Gtk::Label m_TitleLabel;
    Gtk::Label m_TrackLabel;
    Gtk::Label m_YearLabel;
    Gtk::Label m_GenreLabel;
};

#endif

