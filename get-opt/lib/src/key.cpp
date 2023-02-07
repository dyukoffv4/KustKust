#include "key.hpp"

KP::Key::Key(const std::string &l_data) {
    if (l_data.empty()) throw std::invalid_argument("# Key.Key: Name of key can't be empty!");
    this->s_data = '-';
    this->l_data = l_data;
}

KP::Key::Key(const char &s_data, const std::string &l_data) {
    if (s_data == '~') throw std::invalid_argument("# Key.Key: Name '~' has been reserved!");
    if (s_data == '-' && l_data.empty()) throw std::invalid_argument("# Key.Key: Name of key can't be empty!");
    this->s_data = s_data;
    this->l_data = l_data;
}

KP::Key::State KP::Key::getState() const {
    if (s_data == '-' && l_data.empty()) return State::E;
    if (l_data.empty()) return State::S;
    if (s_data == '-') return State::L;
    return State::A;
}

bool KP::Key::operator<(const Key& key) const {
    if (s_data == key.s_data) return l_data < key.l_data;
    return s_data < key.s_data;
}

char KP::Key::sname() const {
    return s_data;
}

std::string KP::Key::lname() const {
    return l_data;
}

KP::Key KP::Key::getNull() {
    Key key('N');
    key.s_data = '-';
    return key;
}

KP::Key KP::Key::getRoot() {
    Key key('N');
    key.s_data = '~';
    return key;
}