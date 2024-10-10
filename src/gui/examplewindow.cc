
#include "examplewindow.h"
#include <array>
#include <iostream>
#include "include/database/models/Rola.h"
#include "include/database/DatabaseUtils.h"

#include "src/gui/MinerDialog.h"

#include <gtkmm/application.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>
#include <gtkmm/filechooserdialog.h>

#include "src/query/queryProcessor.h"



#include <gio/gio.h> 


struct GridEntry {
    std::string m_filename;        // Portada del álbum
    Glib::ustring m_description;   // Descripción formateada
    std::string m_album;           // Nombre del álbum
    std::string m_performer;       // Intérprete
    int m_year;                    // Año
    std::string m_genre;           // Género
    int m_track;                   // Número de pista
};

ExampleWindow::ExampleWindow()
{
    // Cargar el archivo .ui
    auto builder = Gtk::Builder::create_from_file("src/gui/examplewindow.ui");

    // Obtener widgets del archivo UI
    m_MainWindow = builder->get_widget<Gtk::Window>("MainWindow");
    m_ScrolledWindow = builder->get_widget<Gtk::ScrolledWindow>("scrolled_window");
    m_GridView= builder->get_widget<Gtk::GridView>("grid_view");
    m_ButtonBox = builder->get_widget<Gtk::Box>("button_box");
    m_Button_Quit = builder->get_widget<Gtk::Button>("quit_button");

    m_SearchEntry = builder->get_widget<Gtk::Entry>("search_entry");
    m_SearchButton = builder->get_widget<Gtk::Button>("search_button");

    m_SelectFileButton = builder->get_widget<Gtk::Button>("select_file_button");
    

   // Cargar el archivo CSS
    auto cssProvider = Gtk::CssProvider::create();
    auto file = Gio::File::create_for_path("src/gui/style.css"); // Crear un objeto Gio::File
    cssProvider->load_from_file(file);

    // Aplica el CSS al display
    auto display = Gdk::Display::get_default();
    Gtk::StyleContext::add_provider_for_display(display, cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Configurar la ventana principal
    m_MainWindow->set_title("MelodyMiner");

    m_ScrolledWindow->set_expand();

    // Conectar el botón de salir
    m_Button_Quit->signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_quit));

    // Crear el modelo de datos y configurar el GridView
    m_data_model = Gio::ListStore<ModelColumns>::create();
    m_selection_model = Gtk::SingleSelection::create(m_data_model);
    m_selection_model->set_autoselect(false);

    m_factory = Gtk::SignalListItemFactory::create();
    m_factory->signal_setup().connect(sigc::mem_fun(*this, &ExampleWindow::on_setup_listitem));
    m_factory->signal_bind().connect(sigc::mem_fun(*this, &ExampleWindow::on_bind_listitem));

    //fillModelFromRolas(rolas);
    m_data_model->sort(sigc::mem_fun(*this, &ExampleWindow::on_model_sort));

    m_GridView->set_model(m_selection_model);
    m_GridView->set_factory(m_factory);

    m_GridView->signal_activate().connect(sigc::mem_fun(*this, &ExampleWindow::on_item_activated));
    m_selection_model->property_selected().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_selection_changed));

    m_SearchEntry->signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_search_entry_changed));
    m_SearchButton->signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_search_button_clicked));

    m_SelectFileButton->signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_select_file_button_clicked));
    


    m_MainWindow->show();
}


ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit(){
    m_MainWindow->set_visible(false);

    
}

void ExampleWindow::on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto vBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    vBox->set_size_request(120, 170); // Establecer un tamaño fijo para la caja

    auto picture = Gtk::make_managed<Gtk::Picture>();
    picture->set_can_shrink(false);
    picture->set_halign(Gtk::Align::CENTER);
    picture->set_valign(Gtk::Align::END);
    picture->set_size_request(120, 120); // Tamaño fijo para la imagen

    auto label = Gtk::make_managed<Gtk::Label>();
    label->set_size_request(120, 50); // Tamaño fijo para la etiqueta
    label->set_ellipsize(Pango::EllipsizeMode::END); // Para manejar el desbordamiento
    label->set_halign(Gtk::Align::CENTER);

    vBox->append(*picture);
    vBox->append(*label);
    list_item->set_child(*vBox);
}

void ExampleWindow::on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto vBox = dynamic_cast<Gtk::Box*>(list_item->get_child());
    if (!vBox)
        return;
    auto picture = dynamic_cast<Gtk::Picture*>(vBox->get_first_child());
    if (!picture)
        return;
    auto label = dynamic_cast<Gtk::Label*>(picture->get_next_sibling());
    if (!label)
        return;
    picture->set_paintable(col->m_texture);
    label->set_markup(col->m_description);
}

    void ExampleWindow::on_item_activated(unsigned int position)
    {
        auto col = m_data_model->get_item(position);
        if (!col)
            return;

    Rola rola = col->m_rola;

    const std::string filename = col->m_filename;
    const Glib::ustring description = col->m_description;

    RolaDetailWindow detailWindow(rola); // Asegúrate de que `col` contenga la información de `Rola`
    detailWindow.show();
    

    /// 
    auto view = std::make_shared<FormatEditRola>();
    RolaController controller(*view, rola);

    std::cout << "Item activated: filename=" << filename
              << ", description=" << description << std::endl;
}

void ExampleWindow::on_selection_changed()
{
    auto position = m_selection_model->get_selected();
    auto col = m_data_model->get_item(position);
    if (!col)
        return;

    const std::string filename = col->m_filename;
    const Glib::ustring description = col->m_description;

    std::cout << "Selection Changed to: filename=" << filename
              << ", description=" << description << std::endl;
}

int ExampleWindow::on_model_sort(const Glib::RefPtr<const ModelColumns>& a,
                                  const Glib::RefPtr<const ModelColumns>& b)
{
    return (a->m_description < b->m_description) ? -1 : ((a->m_description > b->m_description) ? 1 : 0);
}

void ExampleWindow::add_entry(const std::string& filename,
                               const Glib::ustring& description, const Rola& rola)
{
    try {
        auto pixbuf = Gdk::Pixbuf::create_from_file(filename);

        const int target_width = 120; // ancho deseado
        const int target_height = 120; // alto deseado

        auto scaled_pixbuf = pixbuf->scale_simple(target_width, target_height, Gdk::InterpType::BILINEAR);
        auto texture = Gdk::Texture::create_for_pixbuf(scaled_pixbuf);

        m_data_model->append(ModelColumns::create(filename, description, texture, rola));
    } catch (const Gdk::PixbufError& ex) {
        std::cerr << "Gdk::PixbufError: " << ex.what() << std::endl;
    } catch (const Glib::FileError& ex) {
        std::cerr << "Glib::FileError: " << ex.what() << std::endl;
    }
}

void ExampleWindow::fillModelFromRolas(const std::vector<Rola>& rolas) {
    std::string coverPath = "assets/album_covers/"; // Ruta de la portada

    int i = 1;
    for (const auto& rola : rolas) {
        GridEntry entry;
        entry.m_filename = coverPath + std::to_string((i%6)) +".png"; // Usar la misma portada

        std::string name;

        std::shared_ptr<Album> album = rola.getAlbum();
        if (album) name = album->getName();
        else name = "Unknow";
        entry.m_album = name; // Suponiendo que devuelve std::string
        
        std::shared_ptr<Performer> performer = rola.getPerformer();
        if (performer) name = performer->getName();
        else name = "Unknow";

        entry.m_performer = name; // Suponiendo que devuelve std::string

        entry.m_year = rola.getYear(); // Suponiendo que devuelve int
        entry.m_genre = rola.getGenre(); // Suponiendo que devuelve std::string
        entry.m_track = rola.getTrack(); // Suponiendo que devuelve int

        // Formatear la descripción
        entry.m_description = "<b>" + rola.getTitle() + " </b> \n" +
                              "<b>" + entry.m_album   + " </b> \n" +
                              "<b>"+ entry.m_performer+ " </b> ";

        add_entry(entry.m_filename, entry.m_description, rola); // Usar el método existente para agregar entradas
        i= i +1;
    }
}

Gtk::Window* ExampleWindow::get_window() {
    return m_MainWindow;
}

void ExampleWindow::ExampleWindow::on_search_entry_changed()
{
    Glib::ustring search_text = m_SearchEntry->get_text();
    if(search_text == "") {
        Database db("db/music_database.db");
        RolaDAO rolaDAO(db);
        std::vector<Rola> filteredRolas = rolaDAO.getAll(); // Implementa esta función según tu lógica
        updateModelFromRolas(filteredRolas);
    }
}

void ExampleWindow::on_search_button_clicked()
{
    Glib::ustring search_text = m_SearchEntry->get_text();
    // Aquí puedes implementar la lógica para manejar el texto de búsqueda
    std::cout << "Texto de búsqueda: " << search_text << std::endl;

    std::string resultado = processQuery(search_text);
    std::cout << "Consutal: " << resultado << std::endl;

    Database db("db/music_database.db");
    RolaDAO rolaDAO(db);
    std::vector<Rola> filteredRolas = rolaDAO.executeQuery(resultado); // Implementa esta función según tu lógica

    updateModelFromRolas(filteredRolas);
}


void ExampleWindow::updateModelFromRolas(const std::vector<Rola>& rolas) {
   clearModel();

    int i = 1;
    for (const auto& rola : rolas) {
        GridEntry entry;
        entry.m_filename = "assets/album_covers/" + std::to_string((i % 6)) + ".png"; // Ruta de la portada
        
        std::string name;

        std::shared_ptr<Album> album = rola.getAlbum();
        if (album) name = album->getName();
        else name = "Unknow";
        entry.m_album = name; // Suponiendo que devuelve std::string
        
        std::shared_ptr<Performer> performer = rola.getPerformer();
        if (performer) name = performer->getName();
        else name = "Unknow";

        entry.m_performer = name; // Suponiendo que devuelve std::string

        entry.m_year = rola.getYear();
        entry.m_genre = rola.getGenre();
        entry.m_track = rola.getTrack();

        // Formatear la descripción
        entry.m_description = "<b>" + rola.getTitle() + " </b> | " + entry.m_performer + "\n" +
                              entry.m_album;

        add_entry(entry.m_filename, entry.m_description, rola);
        i = i + 1;
    }
}

void ExampleWindow::clearModel() {
    
    while (m_data_model->get_n_items() > 0) {
        m_data_model->remove(0); 
    }
}


// DÍALOGO
void ExampleWindow::on_select_file_button_clicked() {

    auto dialog = Gtk::FileDialog::create();
    dialog->select_folder(sigc::bind(sigc::mem_fun(
        *this, &ExampleWindow::on_folder_dialog_finish), dialog));
    
}


void ExampleWindow::on_folder_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
  const Glib::RefPtr<Gtk::FileDialog>& dialog){
  try{
    auto folder = dialog->select_folder_finish(result);
    std::cout << "Folder selected: " << folder->get_path() << std::endl;
    
    MinerDialog minerWindow(m_MainWindow, folder->get_path()); // Asegúrate de que `col` contenga la información de `Rola`
    minerWindow.show();

  } catch (const Gtk::DialogError& err){
    std::cout << "No folder selected. " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}





