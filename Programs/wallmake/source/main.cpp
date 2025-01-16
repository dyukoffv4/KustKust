#include <gtkmm.h>
#include <iostream>


class AddButton : public Gtk::Button {
public:
    AddButton() {
        set_margin(10);
        set_label("+");
    }
};

class MainWindow : public Gtk::Window {
public:
    MainWindow() {
        set_title("My App");
        set_size_request(300, 300);
        m_button.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_button_clicked) );
        set_child(m_button);
    }

protected:
    void on_button_clicked() {
        std::cout << "Hello World!" << std::endl;
    }

    AddButton m_button;
};


int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.example");
    return app->make_window_and_run<MainWindow>(argc, argv);
}
