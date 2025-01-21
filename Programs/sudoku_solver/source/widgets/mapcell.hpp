#include <gtkmm/entry.h>


class MapCell : public Gtk::Entry {
public:
    MapCell();
    int get_value() const;

private:
    void on_text_changed();
};
