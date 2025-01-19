#include <gtkmm/entry.h>


class MapCell : public Gtk::Entry {
public:
    MapCell(int index = 0);
    int get_value() const;

    int index;

private:
    void on_text_changed();
};
