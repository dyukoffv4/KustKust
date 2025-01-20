#include <gtkmm.h>
#include <string>
#include <thread>
#include <iostream>

#include "source/utilities/sudoku.hpp"
#include "source/widgets/mapcell.hpp"

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

        for (int i = 0; i < 9; i++) cells.push_back(std::vector<MapCell>(9));
        
        Gtk::Grid main_grid;
        main_grid.set_column_spacing(15);
        main_grid.set_row_spacing(15);
        main_grid.set_margin(15);
        
        for (int i = 0; i < 9; i++) {
            Gtk::Grid temp_grid;
            temp_grid.set_column_spacing(5);
            temp_grid.set_row_spacing(5);
            for (int j = 0; j < 9; j++) {
                temp_grid.attach(cells[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3], j % 3, j / 3);
            }
            main_grid.attach(temp_grid, i % 3, i / 3);
        }

        main_grid.attach(solve_button, 0, 3, 2);
        main_grid.attach(clear_button, 2, 3);

        solve_button.signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_solve_button_clicked) );
        dispatcher.connect( sigc::mem_fun(*this, &MainWindow::sudoku_solve_finish) );
        
        set_child(main_grid);

        success = false;
    }

protected:
    void on_solve_button_clicked() {
        sudoku_solve_start();
    }

    void sudoku_solve_start() {
        widgets_sensetive(false);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (!sudoku.set(i, j, cells[i][j].get_value())) {
                    sudoku.clear();
                    std::cout << "something went wrong at " << i + 1 << ":" << j + 1 << " !\n\n";
                    widgets_sensetive(true);
                    return;
                }
            }
        }

        std::thread([this]() {
            this->success = this->sudoku.solve();
            dispatcher.emit();
        }).detach();
    }

    void sudoku_solve_finish() {
        if (success) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    cells[i][j].set_text(std::to_string(sudoku.get(i, j)));
                }
            }
        }
        else sudoku.clear();

        widgets_sensetive(true);
    }

    void widgets_sensetive(bool value) {
        if (value) solve_button.set_label(SOLVE_BUTTON_DEFAULT);
        else solve_button.set_label(SOLVE_BUTTON_RUNNING);
        solve_button.set_sensitive(value);
        clear_button.set_sensitive(value);
        for (auto &i : cells) for (auto &j : i) j.set_sensitive(value);
    }

    Sudoku sudoku;
    bool success;

    std::vector<std::vector<MapCell>> cells;
    Gtk::Button solve_button;
    Gtk::Button clear_button;
    Glib::Dispatcher dispatcher;
};


int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.example");
    return app->make_window_and_run<MainWindow>(argc, argv);
}
