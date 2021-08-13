#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <map>

// functions

double str_num(std::string str) {

	double num = 0;

	if (!str.empty()) {

		bool minus = false;
		int point = 0;
		for (int i = 0; i < str.size(); i++) {

			if (str[i] == '-') {

				minus = true;
				continue;
			}
			if (str[i] == '.') {

				point = i + 1;
				continue;
			}
			if (str[i] < 48 || str[i] > 57) throw std::domain_error("str_num: Invalid number format!");
			num = num * 10 + (str[i] - 48);
		}

		if (point) num /= pow(10, str.size() - point);
		if (minus) num *= -1;
	}

	return num;
}

std::string num_str(double num) {

	bool minus = (num < 0) ? true : false;
	int num_i = int(abs(num));
	int num_f = int((abs(num) - int(abs(num))) * 100);

	std::string str;
	if (num_f > 0) str = std::string(".") + char(num_f / 10 + 48) + char(num_f % 10 + 48);

	for (int i = num_i; i > 0; i /= 10)
		str = char(i % 10 + 48) + str;

	if (str.empty()) str = "0";
	if (minus) str = "-" + str;

	return str;
}

// classes

typedef std::string Arg;
typedef std::vector<Arg> Args;

class Key {

private:
	std::string data;
	static Key getNull() {

		Key key('N');
		key.data = "-";
		return key;
	}
	static Key getRoot() {

		Key key('N');
		key.data = "~";
		return key;
	}

public:
	explicit Key(const char& data) {

		this->data = data;
	}
	explicit Key(const std::string& data) {

		if (data.empty())
			throw std::invalid_argument("# Key.Key: Name of key can't be empty!");
		this->data = data;
	}

	void rename(const std::string& data) {

		if (data.empty())
			throw std::invalid_argument("# Key.Key: Name of key can't be empty!");
		this->data = data;
	}

	bool largeEqual(const Key& key) const {

		return data == key.data;
	}
	bool shortEqual(const Key& key) const {

		return data[0] == key.data[0];
	}
	
	// stl operator
	bool operator<(const Key& key) const {

		return data[0] < key.data[0];
	}

	std::string name() const {

		return data;
	}

	static Key root_key;
	static Key null_key;
};

Key Key::root_key = Key::getRoot();
Key Key::null_key = Key::getNull();

class Listener {

public:
	virtual Listener* getCopy() = 0;
	virtual void execute(Args) = 0;
};

class Terminal {

private:
	std::map<Key, Listener*> data;

public:
	Terminal() {

		data[Key::root_key] = nullptr;
		data[Key::null_key] = nullptr;
	}
	Terminal(const Terminal& term) {

		for (auto& i : term.data)
			data[i.first] = i.second->getCopy();
	}
	~Terminal() {

		for (auto& i : data)
			if (i.second) delete i.second;
	}

	Terminal& operator=(const Terminal& term) {

		for (auto& i : data)
			if (i.second) delete i.second;
		for (auto& i : term.data)
			data[i.first] = i.second->getCopy();
	}

	void addKey(Key key, Listener* lnr = nullptr) {
	
		if (!data.count(key))
			data[key] = lnr;
	}
	void delKey(Key key) {

		if (data.count(key)) {
			if (data[key]) delete data[key];
			data.erase(data.find(key));
		}
	}

	void attachKey(Key key, Listener* lnr) {

		if (data.count(key)) {
			if (data[key]) delete data[key];
			data[key] = lnr;
		}
	}
	void detachKey(Key key) {

		if (data.count(key)) {
			if (data[key]) delete data[key];
			data[key] = nullptr;
		}
	}

	void attachRoot(Listener* lnr) {

		if (data[Key::root_key]) delete data[Key::root_key];
		data[Key::root_key] = lnr;
	}
	void detachRoot() {

		if (data[Key::root_key]) delete data[Key::root_key];
		data[Key::root_key] = nullptr;
	}
	
	void execute(Args input) {
	
		Key curr_k = Key::root_key;
		Args curr_a;

		for (auto& i : input) {

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
};

// my classes

class MyTerminal : public Terminal {

public:
	int points;
	int radius;
	int center_x;
	int center_y;

	MyTerminal(int p = 10, int r = 1, int cx = 0, int cy = 0) : points(p), radius(r), center_x(cx), center_y(cy) {}
};


class RootLtnr : public Listener {

public:
	virtual Listener* getCopy() {

		return new RootLtnr();
	}

	virtual void execute(Args opts) override {

		std::cout << "> Root arguments: ";
		for (auto& i : opts) std::cout << "\"" + i + "\", ";
		std::cout << ".\n";
	}
};

class CenterLtnr : public Listener {

private:
	MyTerminal* t;

public:
	CenterLtnr(MyTerminal* t) : t(t) {}

	virtual Listener* getCopy() {

		return new CenterLtnr(t);
	}

	virtual void execute(Args opts) override {
	
		if (opts.size() != 2)
			throw std::invalid_argument("CenterLntr.execute: Only two arguments expected after \"c/center\" key!");

		try {
			t->center_x = str_num(opts[0]);
			t->center_y = str_num(opts[1]);
		}
		catch (std::domain_error exp) {

			throw std::invalid_argument(Arg("CenterLntr.execute->") + exp.what());
		}
	}
};

class PointsLtnr : public Listener {

private:
	MyTerminal* t;

public:
	PointsLtnr(MyTerminal* t) : t(t) {}

	virtual Listener* getCopy() {

		return new PointsLtnr(t);
	}

	virtual void execute(Args opts) override {
	
		if (opts.size() != 1)
			throw std::invalid_argument("PointsLntr.execute: Only one argument expected after \"p/points\" key!");
		else {

			try {
				t->points = str_num(opts[0]);
			}
			catch (std::exception exp) {

				throw std::invalid_argument(Arg("PointsLntr.execute->") + exp.what());
			}
		}
	}
};

class RadiusLtnr : public Listener {

private:
	MyTerminal* t;

public:
	RadiusLtnr(MyTerminal* t) : t(t) {}

	virtual Listener* getCopy() {

		return new RadiusLtnr(t);
	}

	virtual void execute(Args opts) override {
	
		if (opts.size() != 1)
			throw std::invalid_argument("RadiusLntr.execute: Only one argument expected after \"r/radius\" key!");
		else {

			try {
				t->radius = str_num(opts[0]);
			}
			catch (std::exception exp) {

				throw std::invalid_argument(Arg("RadiusLntr.execute->") + exp.what());
			}
		}
	}
};

class CircleLtnr : public Listener {

private:
	MyTerminal* t;

public:
	CircleLtnr(MyTerminal* t) : t(t) {}

	virtual Listener* getCopy() {

		return new CircleLtnr(t);
	}

	virtual void execute(Args opts) override {
	
		if (!opts.empty())
			throw std::invalid_argument("CircleLntr.execute: Only keys expected after \"-circle\" key!");
		else {

			std::string xml;
			xml += "> Circle XML: M" + num_str(t->center_x + t->radius) + " " + num_str(t->center_y) + " ";
			for (int i = 1; i < t->points; i++) {

				xml += "L";
				xml += num_str(std::cos(i / double(t->points) * 6.28319) * t->radius + t->center_x) + " ";
				xml += num_str(std::sin(i / double(t->points) * 6.28319) * t->radius + t->center_y) + " ";
			}
			xml += "Z\n";
			std::cout << xml;
		}
	}
};

// main

int main(int argc, char* argv[]) {

	Args data;
	for (int i = 0; i < argc; i++) data.push_back(argv[i]);

	try {
		MyTerminal terminal;
		terminal.attachRoot(new RootLtnr());
		terminal.addKey(Key("center"), new CenterLtnr(&terminal));
		terminal.addKey(Key("points"), new PointsLtnr(&terminal));
		terminal.addKey(Key("radius"), new RadiusLtnr(&terminal));
		terminal.addKey(Key("xmlcrl"), new CircleLtnr(&terminal));
		terminal.execute(data);
	}
	catch (std::invalid_argument e) {

		std::cout << e.what() << "\n";
	}

	return 0;
}