#include <gtkmm.h>

class MyWindow : public Gtk::Window {
public:
    MyWindow();

protected:
    // Signal handlers
    void on_button_clicked();

private:
    Gtk::Button m_button;
};

MyWindow::MyWindow()
    : m_button("Click me") {
    set_title("Ventana Simple");
    set_default_size(200, 100);

    m_button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked));

    set_child(m_button);
}

void MyWindow::on_button_clicked() {
    hide();
}

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    return app->make_window_and_run<MyWindow>(argc, argv);
}
