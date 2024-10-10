#include "src/gui/RolaDetailview.h"

RolaDetailWindow::RolaDetailWindow(const Rola& rola) {
    // Cargar el archivo .ui
    auto builder = Gtk::Builder::create_from_file("src/gui/roladetailwindow.ui");

    // Obtener widgets del archivo UI
    m_MainWindow = builder->get_widget<Gtk::Window>("RolaDetailWindow");
        m_TitleLabel = builder->get_widget<Gtk::Label>("title_label");
        m_AlbumLabel = builder->get_widget<Gtk::Label>("album_label");
        m_PerformerLabel = builder->get_widget<Gtk::Label>("performer_label");
        m_EditButton = builder->get_widget<Gtk::Button>("edit_button" );
        m_DeleteButton = builder->get_widget<Gtk::Button>("delete_button");
        m_CancelButton = builder->get_widget<Gtk::Button>("cancel_button");

    // Configurar las etiquetas con la información de la rola
    m_TitleLabel->set_text("Título: " + rola.getTitle());

    std::string name;

    std::shared_ptr<Album> album = rola.getAlbum();
    if (album) name = album->getName();
    else name = "Unknow";
    m_AlbumLabel->set_text("Álbum: " + name);
        
    std::shared_ptr<Performer> performer = rola.getPerformer();
    if (performer) name = performer->getName();
    else name = "Unknow";
    m_PerformerLabel->set_text("Intérprete: " + name);

    // Conectar señales de los botones
    m_EditButton->signal_clicked().connect([this]() {
        // Lógica para editar
    });
    m_DeleteButton->signal_clicked().connect([this]() {
        // Lógica para eliminar
    });
    m_CancelButton->signal_clicked().connect([this]() {
        //
    });

    m_MainWindow->show();


}
