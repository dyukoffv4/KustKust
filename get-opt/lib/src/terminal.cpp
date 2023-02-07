#include "terminal.hpp"

KP::Terminal::Terminal() {
    binds[Key::getRoot()] = nullptr;
    binds[Key::getNull()] = nullptr;
}

KP::Terminal::Terminal(const Terminal &term) {
    for (auto &i : term.binds) binds[i.first] = i.second;
}

KP::Terminal &KP::Terminal::operator=(const Terminal &term) {
    binds.clear();
    for (auto &i : term.binds) binds[i.first] = i.second;
    return *this;
}

void KP::Terminal::setKey(Key key, void (*lnr)(Args)) {
    if (key.getState() == Key::State::A) {
        binds[Key(key.lname())] = lnr;
        binds[Key(key.sname())] = lnr;
    }
    else binds[key] = lnr;
}

void KP::Terminal::delKey(Key key) {
    if (key.getState() == Key::State::A) {
        if (binds.count(Key(key.lname()))) binds.erase(binds.find(Key(key.lname())));
        if (binds.count(Key(key.sname()))) binds.erase(binds.find(Key(key.sname())));
    }
    else if (binds.count(key)) binds.erase(binds.find(key));
}

void KP::Terminal::setRoot(void (*lnr)(Args)) {
    binds[Key::getRoot()] = lnr;
}

void KP::Terminal::delRoot() {
    binds[Key::getRoot()] = nullptr;
}

void KP::Terminal::setFinal(void (*lnr)(Args)) {
    last = lnr;
}

void KP::Terminal::delFinal() {
    last = nullptr;
}

void KP::Terminal::cleanBinds() {
    last = nullptr;
    binds.clear();
    binds[Key::getRoot()] = nullptr;
    binds[Key::getNull()] = nullptr;
}

void KP::Terminal::execute(int argc, char* argv[]) {
    Args data;
	for (int i = 0; i < argc; i++) data.push_back(argv[i]);
    execute(data);
}

void KP::Terminal::execute(Args input) {
    Key curr_k = Key::getRoot();
    Args curr_a;
    int curr_i = 0;

    for (auto &i : input) {
        if (i[0] == '-') {
            // Option Key
            if ((i.size() == 3 && i[1] == '-') || (i.size() >= 3 && i[1] == '-' && i[2] == '-')) {
                curr_a.push_back(i.substr(1));
                continue;
            }

            // Task Execute
            if (curr_k[curr_i] == Key::Dind::e) {
                try {
                    if (binds[curr_k]) binds[curr_k](curr_a);
                }
                catch (std::invalid_argument e) {
                    std::cout << "# Terminal.execute->" << e.what() << "\n";
                }
            }
            else std::cout << "# Terminal.execute: Wrong number of parametrs!\n";

            // New Key
            curr_i = 0;
            curr_a.clear();
            curr_k = Key::getNull();
            if (i.size() == 1) std::cout << "# Terminal.execute: Key expected after \"-\"!\n";
            else {
                if (i.size() > 1 && i[1] == '-') {
                    if (i.size() == 2) std::cout << "# Terminal.execute: Key expected after \"--\"!\n";
                    else {
                        if (binds.count(Key(i.substr(2)))) curr_k = binds.find(Key(i.substr(2)))->first;
                        else std::cout << "# Terminal.execute: Key with name \"" + i.substr(2) + "\" doesn't exist!\n";
                    }
                }
                else {
                    if (i.size() > 2) std::cout << "# Terminal.execute: Short key expected after \"-\"!\n";
                    else {
                        if (binds.count(Key(i[1]))) curr_k = binds.find(Key(i[1]))->first;
                        else std::cout << std::string("# Terminal.execute: Key with name \"") + i[1] + "\" doesn't exist!\n";
                    }
                }
            }
        }
        else {
            curr_i++;
            if (curr_k[curr_i] == Key::Dind::h) {
                try {
                    if (binds[curr_k]) binds[curr_k](curr_a);   // Task Execute
                }
                catch (std::invalid_argument e) {
                    std::cout << "# Terminal.execute->" << e.what() << "\n";
                }
                std::cout << "# Terminal.execute: Wrong number of parametrs!\n";
                curr_i = 1;
                curr_a.clear();
                curr_k = Key::getNull();
            }
            curr_a.push_back(i);
        }
    }

    // Task Execute
    if (curr_k[curr_i] == Key::Dind::e) {
        try {
            if (binds[curr_k]) binds[curr_k](curr_a);
        }
        catch (std::invalid_argument e) {
            std::cout << "# Terminal.execute->" << e.what() << "\n";
        }
    }
    else std::cout << "# Terminal.execute: Wrong number of parametrs!\n";

    // Final Execute
    try {
        if (last) last(curr_a);
    }
    catch (std::invalid_argument e) {
        std::cout << "# Terminal.execute->" << e.what() << "\n";
    }
}