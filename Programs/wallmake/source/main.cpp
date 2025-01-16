#include <gtkmm.h>
#include <iostream>


class HelloWorld : public Gtk::Window {
public:
    HelloWorld() : m_button("Hello World") {
        m_button.set_margin(10);
        m_button.signal_clicked().connect(sigc::mem_fun(*this, &HelloWorld::on_button_clicked));
        set_child(m_button);
    }

    ~HelloWorld() override {}

protected:
    void on_button_clicked() {
        std::cout << "Hello World" << std::endl;
    }

    Gtk::Button m_button;
};


int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.example");
    return app->make_window_and_run<HelloWorld>(argc, argv);
}
