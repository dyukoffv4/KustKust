#include "key.hpp"

KP::Key::Key(const char &s_data, int num, int hnum) {
    if (s_data == '~') throw std::invalid_argument("# Key.Key: Name '~' has been reserved!");
    if (s_data == '-') throw std::invalid_argument("# Key.Key: Name of key can't be empty!");
    this->s_data = s_data;
    this->setDiapozon(num, hnum);
}

KP::Key::Key(const std::string &l_data, int num, int hnum) {
    if (l_data.empty()) throw std::invalid_argument("# Key.Key: Name of key can't be empty!");
    this->s_data = '-';
    this->l_data = l_data;
    this->setDiapozon(num, hnum);
}

KP::Key::Key(const char &s_data, const std::string &l_data, int num, int hnum) {
    if (s_data == '~') throw std::invalid_argument("# Key.Key: Name '~' has been reserved!");
    if (s_data == '-' && l_data.empty()) throw std::invalid_argument("# Key.Key: Name of key can't be empty!");
    this->s_data = s_data;
    this->l_data = l_data;
    this->setDiapozon(num, hnum);
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

bool KP::Key::operator[](const int& num) const {
    if (lk_num == -1) return true;
    if (lk_num == 0 && hk_num <= 0 && num > 0) return false;
    return lk_num <= num && hk_num >= num;
}

char KP::Key::sname() const {
    return s_data;
}

std::string KP::Key::lname() const {
    return l_data;
}

KP::Key KP::Key::getNull() {
    Key key('N', 0);
    key.s_data = '-';
    return key;
}

KP::Key KP::Key::getRoot() {
    Key key('N');
    key.s_data = '~';
    return key;
}

void KP::Key::setDiapozon(int f, int s) {
    if (f > s && s != -1) throw std::invalid_argument("# Key.setDiapozon: First num can't be bigger then second!");
    if (s > -1) {
        if (f > -1) lk_num = f;
        else lk_num = 0;
        hk_num = s;
        return;
    }
    if (f > -1) {
        hk_num = f;
        lk_num = 0;
        return;
    }
    hk_num = lk_num = -1;
}