#include "terminal.hpp"


Terminal::Terminal() {
    data[Key::root_key] = nullptr;
    data[Key::null_key] = nullptr;
}

Terminal::Terminal(const Terminal &term) {
    for (auto &i : term.data) data[i.first] = i.second->getCopy();
}

Terminal::~Terminal() {
    for (auto &i : data) if (i.second) delete i.second;
}

Terminal &Terminal::operator=(const Terminal &term) {
    for (auto &i : data) if (i.second) delete i.second;
    for (auto &i : term.data) data[i.first] = i.second->getCopy();
    return *this;
}

void Terminal::addKey(Key key, Listener *lnr) {
    if (!data.count(key)) data[key] = lnr;
}

void Terminal::delKey(Key key) {
    if (data.count(key)) {
        if (data[key]) delete data[key];
        data.erase(data.find(key));
    }
}

void Terminal::attachKey(Key key, Listener *lnr) {
    if (data.count(key)) {
        if (data[key]) delete data[key];
        data[key] = lnr;
    }
}

void Terminal::detachKey(Key key) {
    if (data.count(key)) {
        if (data[key]) delete data[key];
        data[key] = nullptr;
    }
}

void Terminal::attachRoot(Listener *lnr) {
    if (data[Key::root_key]) delete data[Key::root_key];
    data[Key::root_key] = lnr;
}

void Terminal::detachRoot() {
    if (data[Key::root_key]) delete data[Key::root_key];
    data[Key::root_key] = nullptr;
}

void Terminal::execute(Args input) {
    Key curr_k = Key::root_key;
    Args curr_a;

    for (auto &i : input) {
        if (i[0] == '-') {
            // previous task execute
            try {
                if (data[curr_k]) data[curr_k]->execute(curr_a);
            }
            catch (std::invalid_argument e) {
                std::cout << "# Terminal.execute->" << e.what() << "\n";
            }
            curr_a.clear();
            curr_k = Key::null_key;

            // new key finding
            if (i.size() < 2) std::cout << "# Terminal.execute: Key expected after \"-\"!\n";
            else {
                if (i.size() > 1 && i[1] == '-') {
                    if (i.size() < 3) std::cout << "# Terminal.execute: Key expected after \"--\"!\n";
                    else {
                        if (data.count(Key(i[2])) && data.find(Key(i[2]))->first.name() == i.substr(2, i.size() - 1)) curr_k = Key(i[2]);
                        else std::cout << "# Terminal.execute: Key with name \"" + i.substr(2, i.size() - 1) + "\" doesn't exist!\n";
                    }
                }
                else {
                    if (i.size() > 2) std::cout << "# Terminal.execute: Short key expected after \"-\"!\n";
                    else {
                        if (data.count(Key(i[1]))) curr_k = Key(i[1]);
                        else std::cout << Arg("# Terminal.execute: Key with name \"") + i[1] + "\" doesn't exist!\n";
                    }
                }
            }
        }
        else curr_a.push_back(i);
    }
    try {
        if (data[curr_k]) data[curr_k]->execute(curr_a);
    }
    catch (std::invalid_argument e) {
        std::cout << "# Terminal.execute->" << e.what() << "\n";
    }
}