#include "terminal.hpp"

Terminal::Terminal() {
    binds[Key::getRoot()] = nullptr;
    binds[Key::getNull()] = nullptr;
}

Terminal::Terminal(const Terminal &term) {
    for (auto &i : term.binds) binds[i.first] = i.second;
}

Terminal &Terminal::operator=(const Terminal &term) {
    binds.clear();
    for (auto &i : term.binds) binds[i.first] = i.second;
    return *this;
}

void Terminal::setKey(Key key, void (*lnr)(Args)) {
    if (key.getState() == Key::State::A) {
        binds[Key(key.lname())] = lnr;
        binds[Key(key.sname())] = lnr;
    }
    else binds[key] = lnr;
}

void Terminal::delKey(Key key) {
    if (key.getState() == Key::State::A) {
        if (binds.count(Key(key.lname()))) binds.erase(binds.find(Key(key.lname())));
        if (binds.count(Key(key.sname()))) binds.erase(binds.find(Key(key.sname())));
    }
    else if (binds.count(key)) binds.erase(binds.find(key));
}

void Terminal::setRoot(void (*lnr)(Args)) {
    binds[Key::getRoot()] = lnr;
}

void Terminal::delRoot() {
    binds[Key::getRoot()] = nullptr;
}

void Terminal::execute(Args input) {
    Key curr_k = Key::getRoot();
    Args curr_a;

    for (auto &i : input) {
        if (i[0] == '-') {
            // extra key checkout
            if ((i.size() == 3 && i[1] == '-') || (i.size() >= 3 && i[1] == '-' && i[2] == '-')) {
                curr_a.push_back(i.substr(1));
                continue;
            }

            // previous task execute
            try {
                if (binds[curr_k]) binds[curr_k](curr_a);
            }
            catch (std::invalid_argument e) {
                std::cout << "# Terminal.execute->" << e.what() << "\n";
            }
            curr_a.clear();
            curr_k = Key::getNull();

            // new key finding
            if (i.size() == 1) std::cout << "# Terminal.execute: Key expected after \"-\"!\n";
            else {
                if (i.size() > 1 && i[1] == '-') {
                    if (i.size() == 2) std::cout << "# Terminal.execute: Key expected after \"--\"!\n";
                    else {
                        if (binds.count(Key(i.substr(2)))) curr_k = Key(i.substr(2));
                        else std::cout << "# Terminal.execute: Key with name \"" + i.substr(2) + "\" doesn't exist!\n";
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
        if (binds[curr_k]) binds[curr_k](curr_a);
    }
    catch (std::invalid_argument e) {
        std::cout << "# Terminal.execute->" << e.what() << "\n";
    }
}