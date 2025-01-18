#include <gtkmm.h>
#include <string>
#include <thread>
#include <iostream>

#include "source/utilities/test.hpp"

#define SOLVE_BUTTON_DEFAULT "Solve"
#define SOLVE_BUTTON_RUNNING "Solving..."
#define CLEAR_BUTTON_DEFAULT "Clear"


class MainWindow : public Gtk::Window {
public:
    MainWindow() : sudoku(nullptr) {
        set_title("Sudoku Solver");

        solve_button.set_label(SOLVE_BUTTON_DEFAULT);
        clear_button.set_label(CLEAR_BUTTON_DEFAULT);

        buttons_map = std::vector<std::vector<Gtk::Button>>(9);
        for (auto &i : buttons_map) i = std::vector<Gtk::Button>(9);
        
        Gtk::Grid main_grid;
        main_grid.set_column_spacing(15);
        main_grid.set_row_spacing(15);
        main_grid.set_margin(15);
        
        for (int i = 0; i < 9; i++) {
            Gtk::Grid temp_grid;
            temp_grid.set_column_spacing(5);
            temp_grid.set_row_spacing(5);
            for (int j = 0; j < 9; j++) {
                Gtk::Button& slot = buttons_map[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3];
                slot.set_label(std::to_string(i * 9 + j));
                slot.set_size_request(50, 50);
                temp_grid.attach(slot, j % 3, j / 3);
            }
            main_grid.attach(temp_grid, i % 3, i / 3);
        }

        main_grid.attach(solve_button, 0, 3, 2);
        main_grid.attach(clear_button, 2, 3);

        solve_button.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_solve_button_clicked) );
        dispatcher.connect( sigc::mem_fun(*this, &MainWindow::with_task_finished) );
        
        set_child(main_grid);
    }

    ~MainWindow() {
        if (sudoku != nullptr) delete sudoku;
    }

protected:
    void on_solve_button_clicked() {
        with_task_started();

        auto data = Sudoku::map(9);
        for (int i = 0; i < 9; i++) {
            data[i] = std::vector<int>(9);
            for (int j = 0; j < 9; j++) {
                std::string label = buttons_map[i][j].get_label();
                data[i][j] = label.empty() ? 0 : std::stoi(label);
            }
        }

        if (sudoku != nullptr) delete sudoku;
        sudoku = new Sudoku(data);

        std::thread([this]() {
            try {
                // some work
                // bool health = sudoku->check_health();
                // ...
            }
            catch (std::exception e) {
                std::cout << e.what();
            }

            dispatcher.emit();
        }).detach();
    }

    void with_task_started() {
        solve_button.set_label(SOLVE_BUTTON_RUNNING);
        solve_button.set_sensitive(false);
        clear_button.set_sensitive(false);
        for (auto &i : buttons_map) for (auto &j : i) j.set_sensitive(false);
    }

    void with_task_finished() {
        solve_button.set_label(SOLVE_BUTTON_DEFAULT);
        solve_button.set_sensitive(true);
        clear_button.set_sensitive(true);
        for (auto &i : buttons_map) for (auto &j : i) j.set_sensitive(true);
    }

    Sudoku* sudoku;

    std::vector<std::vector<Gtk::Button>> buttons_map;
    Gtk::Button solve_button;
    Gtk::Button clear_button;
    Glib::Dispatcher dispatcher;
};


int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.example");
    return app->make_window_and_run<MainWindow>(argc, argv);
}
