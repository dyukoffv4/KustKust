#include <gtkmm.h>
#include <thread>

#include "source/widgets/gamemap.hpp"

#define SOLVE_BUTTON_DEFAULT "Solve"
#define SOLVE_BUTTON_RUNNING "Solving..."
#define CLEAR_BUTTON_DEFAULT "Clear"
#define CLEAR_BUTTON_SUCCESS "Clear Answer"


class MainWindow : public Gtk::Window {
public:
    MainWindow() {
        set_title("Sudoku Solver");

        solve_button.set_label(SOLVE_BUTTON_DEFAULT);
        clear_button.set_label(CLEAR_BUTTON_DEFAULT);

        Gtk::Grid main_grid;
        main_grid.set_column_spacing(15);
        main_grid.set_row_spacing(15);
        main_grid.set_margin(15);

        main_grid.attach(table, 0, 0, 3);
        main_grid.attach(solve_button, 0, 1, 2);
        main_grid.attach(clear_button, 2, 1);

        set_child(main_grid);

        solve_button.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_solve_button_clicked) );
        clear_button.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_clear_button_clicked) );
        dispatcher.connect( sigc::mem_fun(*this, &MainWindow::sudoku_solve_finish) );

        success = false;
    }

protected:
    void on_solve_button_clicked() {
        sudoku_solve_start();
    }

    void on_clear_button_clicked() {
        table.clear();
        if (success && !(success = false)) clear_button.set_label(CLEAR_BUTTON_DEFAULT);
    }

    void sudoku_solve_start() {
        widgets_sensetive(false);
        if (table.setup()) {
            std::thread([this]() {
                this->success = this->table.solve();
                dispatcher.emit();
            }).detach();
        }
        else widgets_sensetive(true);
    }

    void sudoku_solve_finish() {
        if (success) {
            table.print();
            clear_button.set_label(CLEAR_BUTTON_SUCCESS);
        }
        widgets_sensetive(true);
    }

    void widgets_sensetive(bool value) {
        if (value) solve_button.set_label(SOLVE_BUTTON_DEFAULT);
        else solve_button.set_label(SOLVE_BUTTON_RUNNING);
        solve_button.set_sensitive(value);
        clear_button.set_sensitive(value);
        table.set_sensitive(value);
    }

    bool success;
    GameMap table;
    Gtk::Button solve_button;
    Gtk::Button clear_button;
    Glib::Dispatcher dispatcher;
};


int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.example");
    return app->make_window_and_run<MainWindow>(argc, argv);
}
