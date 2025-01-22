#pragma once

#include <gtkmm/entry.h>


class MapCell : public Gtk::Entry {
public:
    MapCell();
    int get_value() const;

protected:
    void on_changed() override;
};
