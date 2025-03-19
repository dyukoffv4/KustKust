#pragma once

#include <gtkmm/grid.h>
#include <gtkmm/eventcontrollerkey.h>

#include "mapcell.hpp"
#include "source/sudoku/algs.hpp"

class GameMap : public Gtk::Grid {
public:
    GameMap();

    bool setup();
    bool solve();
    void print();
    void clear();

protected:
    bool on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state, int row, int col);

    std::vector<std::vector<MapCell>> cells;
    Solver sudoku_solver;
    bool success;
};
