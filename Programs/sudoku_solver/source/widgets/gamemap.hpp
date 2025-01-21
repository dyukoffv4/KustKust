#pragma once

#include <gtkmm/grid.h>
#include "mapcell.hpp"
#include "source/utilities/sudoku.hpp"


class GameMap : public Gtk::Grid {
public:
    GameMap();

    bool setup();
    bool solve();
    void print();
    void clear();

private:
    std::vector<std::vector<MapCell>> cells;
    Sudoku sudoku;
    bool success;
};
