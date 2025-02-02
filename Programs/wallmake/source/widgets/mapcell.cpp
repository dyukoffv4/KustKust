#include "mapcell.hpp"


MapCell::MapCell(int index) : index(index) {
    set_max_length(1);
    set_size_request(50, 50);
    set_alignment(Gtk::Align::CENTER);
    signal_changed().connect(sigc::mem_fun(*this, &MapCell::on_text_changed));
}

int MapCell::get_value() const {
    try {
        return std::stoi(get_text());
    } catch (...) {
        return 0;
    }
}

void MapCell::on_text_changed() {
    auto text = get_text();

    if (!text.empty() && (text[0] < '1' || text[0] > '9')) set_text("");
}
