#include <gtkmm.h>
#include <vector>
#include <string>
#include <thread>
#include <iostream>


class NineGroup : public Gtk::Grid {
public:
    NineGroup() : buttons(9) {
        for (int i = 0; i < 9; i++) {
            buttons[i].set_label(std::to_string(i + 1));
            buttons[i].set_margin(5);
            buttons[i].set_size_request(50, 50);
            attach(buttons[i], i % 3, i / 3);
        }
        set_margin(5);
    }

    std::vector<Gtk::Button> buttons;
};

class MainWindow : public Gtk::Window {
public:
    MainWindow() : nine_groups(9) {
        set_title("Sudoku Solver");

        solve_button.set_margin(10);
        solve_button.set_margin_bottom(20);
        solve_button.set_label("Solve");
        solve_button.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_button_clicked) );

        dispatcher.connect( sigc::mem_fun(*this, &MainWindow::on_task_finished) );
        
        for (int i = 0; i < 9; i++) main_grid.attach(nine_groups[i], i % 3, i / 3);
        main_grid.attach(solve_button, 0, 3, 3);
        set_child(main_grid);
    }

protected:
    void on_button_clicked() {
        solve_button.set_sensitive(false);

        std::thread([this]() {
            int sum = 0;
            for (int i = 0; i < 100000; i++) for (int j = 0; j < 100000; j++) sum++;
            std::cout << sum << std::endl;
            dispatcher.emit();
        }).detach();
    }

    void on_task_finished() {
        solve_button.set_sensitive(true);
    }

    std::vector<NineGroup> nine_groups;
    Gtk::Button solve_button;
    Gtk::Grid main_grid;
    Glib::Dispatcher dispatcher;
};


int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.example");
    return app->make_window_and_run<MainWindow>(argc, argv);
}
