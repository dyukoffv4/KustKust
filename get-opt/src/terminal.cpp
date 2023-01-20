#include "terminal.hpp"


Listener::Listener(Terminal* _term) {
    this->term = _term;
}

Terminal::Terminal() {
    binds[Key::root_key] = nullptr;
    binds[Key::null_key] = nullptr;
}

Terminal::Terminal(const Terminal &term) {
    for (auto &i : term.binds) binds[i.first] = i.second->getCopy();
    for (auto &i : term.data) data[i.first] = i.second;
}

Terminal::~Terminal() {
    for (auto &i : binds) if (i.second) delete i.second;
}

Terminal &Terminal::operator=(const Terminal &term) {
    for (auto &i : binds) if (i.second) delete i.second;
    binds.clear();
    for (auto &i : term.binds) binds[i.first] = i.second->getCopy();
    data.clear();
    for (auto &i : term.data) data[i.first] = i.second;
    return *this;
}

int& Terminal::Data(std::string key) {
    if (!data[key]) data[key] = 0;
    return data[key];
}

void Terminal::setKey(Key key, Listener *lnr) {
    if (binds.count(key) && binds[key]) delete binds[key];
    binds[key] = lnr;
}

void Terminal::delKey(Key key) {
    if (binds.count(key)) {
        if (binds[key]) delete binds[key];
        binds.erase(binds.find(key));
    }
}

void Terminal::setRoot(Listener *lnr) {
    if (binds[Key::root_key]) delete binds[Key::root_key];
    binds[Key::root_key] = lnr;
}

void Terminal::delRoot() {
    if (binds[Key::root_key]) delete binds[Key::root_key];
    binds[Key::root_key] = nullptr;
}

void Terminal::execute(Args input) {
    Key curr_k = Key::root_key;
    Args curr_a;

    for (auto &i : input) {
        if (i[0] == '-') {
            // previous task execute
            try {
                if (binds[curr_k]) binds[curr_k]->execute(curr_a);
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
                        if (binds.count(Key(i[2])) && binds.find(Key(i[2]))->first.name() == i.substr(2, i.size() - 1)) curr_k = Key(i[2]);
                        else std::cout << "# Terminal.execute: Key with name \"" + i.substr(2, i.size() - 1) + "\" doesn't exist!\n";
                    }
                }
                else {
                    if (i.size() > 2) std::cout << "# Terminal.execute: Short key expected after \"-\"!\n";
                    else {
                        if (binds.count(Key(i[1]))) curr_k = Key(i[1]);
                        else std::cout << Arg("# Terminal.execute: Key with name \"") + i[1] + "\" doesn't exist!\n";
                    }
                }
            }
        }
        else curr_a.push_back(i);
    }
    try {
        if (binds[curr_k]) binds[curr_k]->execute(curr_a);
    }
    catch (std::invalid_argument e) {
        std::cout << "# Terminal.execute->" << e.what() << "\n";
    }
}