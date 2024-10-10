#include "src/gui/dialog/FormatEditRola.h"
#include <iostream>

FormatEditRola::FormatEditRola() : Gtk::Dialog("Edit Rola") {
    auto grid = Gtk::make_managed<Gtk::Grid>();
    get_content_area()->append(*grid);

    m_TitleLabel.set_text("Title:");
    m_TrackLabel.set_text("Track:");
    m_YearLabel.set_text("Year:");
    m_GenreLabel.set_text("Genre:");

    grid->attach(m_TitleLabel, 0, 0);
    grid->attach(m_TitleEntry, 1, 0);
    grid->attach(m_TrackLabel, 0, 1);
    grid->attach(m_TrackEntry, 1, 1);
    grid->attach(m_YearLabel, 0, 2);
    grid->attach(m_YearEntry, 1, 2);
    grid->attach(m_GenreLabel, 0, 3);
    grid->attach(m_GenreEntry, 1, 3);

    add_button("_OK", Gtk::ResponseType::OK);
    add_button("_Cancel", Gtk::ResponseType::CANCEL);

    show();
}

void FormatEditRola::set_initial_data(const Rola& rola) {
    m_TitleEntry.set_text(rola.getTitle());
    m_TrackEntry.set_text(std::to_string(rola.getTrack()));
    m_YearEntry.set_text(std::to_string(rola.getYear()));
    m_GenreEntry.set_text(rola.getGenre());
}

std::string FormatEditRola::get_title() const {
    return m_TitleEntry.get_text();
}

int FormatEditRola::get_track() const {
    return std::stoi(m_TrackEntry.get_text());
}

int FormatEditRola::get_year() const {
    return std::stoi(m_YearEntry.get_text());
}

std::string FormatEditRola::get_genre() const {
    return m_GenreEntry.get_text();
}
