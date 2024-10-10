// #include <gtkmm.h>
// #include <iostream>
// #include <vector>

// // Clase Rola
// class Raaola {
// public:
//     Rola(const std::string& nombre) : nombre(nombre) {}
//     std::string getNombre() const { return nombre; }

// private:
//     std::string nombre;
// };

// // Namespace anónimo para manejar la lógica
// namespace {
//     Gtk::Window* pMainWindow = nullptr;
//     Glib::RefPtr<Gtk::Application> app;
//     Gtk::Grid* pGrid = nullptr;
//     std::vector<Rola> rolas;

//     void on_button_clicked(int index)
//     {
//         // Aquí puedes manejar los clicks en los botones del sidebar
//         std::cout << "Botón " << index << " presionado." << std::endl;
//     }

//     void populate_grid()
//     {
//         for (size_t i = 0; i < rolas.size(); ++i) {
//             Gtk::Label* label = Gtk::manage(new Gtk::Label(rolas[i].getNombre()));
//             pGrid->attach(*label, 0, i, 1, 1); // Coloca el label en la grid
//         }
//     }

//     void on_app_activate() {
//         // Cargar el archivo GtkBuilder y crear los widgets
//         auto refBuilder = Gtk::Builder::create();
//         try {
//             refBuilder->add_from_file("src/gui/interface.ui");
//         } catch(const Glib::FileError& ex) {
//             std::cerr << "FileError: " << ex.what() << std::endl;
//             return;
//         } catch(const Glib::MarkupError& ex) {
//             std::cerr << "MarkupError: " << ex.what() << std::endl;
//             return;
//         } catch(const Gtk::BuilderError& ex) {
//             std::cerr << "BuilderError: " << ex.what() << std::endl;
//             return;
//         }

//         // Obtener la ventana principal
//         pMainWindow = refBuilder->get_widget<Gtk::Window>("main_window");
//         if (!pMainWindow) {
//             std::cerr << "Could not get the main window" << std::endl;
//             return;
//         }

//         // Obtener la grid y almacenar la referencia
//         pGrid = refBuilder->get_widget<Gtk::Grid>("my_grid");
//         if (!pGrid) {
//             std::cerr << "Could not get the grid" << std::endl;
//             return;
//         }

//         // Agregar Rolas al vector
//        

//         populate_grid();

//         // Conectar botones en el sidebar a las funciones
//         for (int i = 0; i < 5; ++i) {
//             auto button = refBuilder->get_widget<Gtk::Button>("button" + std::to_string(i + 1));
//             if (button) {
//                 button->signal_clicked().connect([i]() { on_button_clicked(i + 1); });
//             }
//         }

//         app->add_window(*pMainWindow);
//         pMainWindow->set_visible(true);
//     }
// } // namespace anónima

// int main(int argc, char** argv)
// {
//     app = Gtk::Application::create("org.gtkmm.example");
//     app->signal_activate().connect([]() { on_app_activate(); });
//     return app->run(argc, argv);
// }
