#include "key.hpp"


Key Key::getNull() {
    Key key('N');
    key.data = "-";
    return key;
}

Key Key::getRoot() {
    Key key('N');
    key.data = "~";
    return key;
}

Key::Key(const char &data) {
    this->data = data;
}

Key::Key(const std::string &data) {
    if (data.empty()) throw std::invalid_argument("# Key.Key: Name of key can't be empty!");
    this->data = data;
}

void Key::rename(const std::string &data) {
    if (data.empty()) throw std::invalid_argument("# Key.Key: Name of key can't be empty!");
    this->data = data;
}

bool Key::largeEqual(const Key &key) const {
    return data == key.data;
}

bool Key::shortEqual(const Key &key) const {
    return data[0] == key.data[0];
}

bool Key::operator<(const Key &key) const {
    return data[0] < key.data[0];
}

std::string Key::name() const {
    return data;
}

Key Key::root_key = Key::getRoot();
Key Key::null_key = Key::getNull();