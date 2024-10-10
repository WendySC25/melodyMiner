#include "src/gui/dialog/RolaController.h"
#include "include/database/models/Rola.h"
#include <iostream>

RolaController::RolaController(FormatEditRola& view, Rola& model)
    : m_View(view), m_Model(model) {

    m_View.signal_response().connect(sigc::mem_fun(*this, &RolaController::on_dialog_response));
    m_View.set_initial_data(m_Model);
    
}

void RolaController::on_dialog_response(int response) {
    std::cout << "Response: " << response << std::endl;
    if (response == Gtk::ResponseType::OK) {
        // Actualizar el modelo con los datos de la vista
        m_Model.setTitle(m_View.get_title());
        m_Model.setTrack(m_View.get_track());
        m_Model.setYear(m_View.get_year());
        m_Model.setGenre(m_View.get_genre());

        std::cout << "ROLA: " << m_Model.getTitle();
    }
}
