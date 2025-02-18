#include "mapcell.hpp"

MapCell::MapCell() {
    set_max_length(1);
    set_size_request(50, 50);
    set_alignment(Gtk::Align::CENTER);
}

int MapCell::get_value() const {
    try {
        return std::stoi(get_text());
    } catch (...) {
        return 0;
    }
}

void MapCell::on_changed() {
    auto text = get_text();
    if (!text.empty() && (text[0] < '1' || text[0] > '9')) set_text("");
    Entry::on_changed();
}
