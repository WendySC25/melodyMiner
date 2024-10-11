
#include "melodyMinerWindow.h"
#include <gtkmm/application.h>
#include "include/database/models/Rola.h"
#include "include/database/DatabaseUtils.h"

int main(int argc, char *argv[]){
  auto app = Gtk::Application::create("org.gtkmm.example");
  return app->make_window_and_run<MelodyMinerWindow>(argc, argv);
}
