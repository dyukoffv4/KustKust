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
			if (str[i] < 48 || str[i] > 57) throw std::exception("# str_num: Invalid number format!");
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

	Key() : data("") {}

public:
	Key(const std::string& data) : data(data) {

		if (data.empty())
			throw std::exception("# Key.Key: Name of key can't be empty!");
	}

	bool sEqual(const Key& key) const {

		if (data.empty() && key.data.empty()) return true;
		if (data.empty() || key.data.empty()) return false;
		return data[0] == key.data[0];
	}
	bool aEqual(const Key& key) const {

		return data == key.data;
	}

	bool sEqual(const std::string& str) const {

		if (data.empty() && str.empty()) return true;
		if (data.empty() || str.empty()) return false;
		return data[0] == str[0];
	}
	bool aEqual(const std::string& str) const {

		return data == str;
	}
	
	bool operator<(const Key& key) const {

		if (data.empty() && key.name().empty()) return false;
		if (data.empty()) return true;
		return data[0] < key.data[0];
	}

	std::string name() const {

		return data;
	}

	static Key getNullKey() {

		return Key();
	}
};

class Listener {

public:
	virtual void execute(Args) = 0;
};

class Terminal {

private:
	std::map<Key, Listener*> data;

public:
	Terminal() {

		data[Key::getNullKey()] = nullptr;
	}
	~Terminal() {

		for (auto& i : data)
			if (i.second) delete i.second;
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

		if (data[Key::getNullKey()]) delete data[Key::getNullKey()];
		data[Key::getNullKey()] = lnr;
	}
	void detachRoot() {

		if (data[Key::getNullKey()]) delete data[Key::getNullKey()];
		data[Key::getNullKey()] = nullptr;
	}
	
	void execute(Args input) {
	
		Key curr_k = Key::getNullKey();
		Args curr_a;

		for (auto& i : input) {

			if (i[0] == '-') {

				if (data[curr_k]) data[curr_k]->execute(curr_a);
				curr_a.clear();

				bool new_key = false;
				for (auto& j : data) {

					if (j.first.aEqual(i.substr(1, i.size() - 1))) {

						curr_k = j.first;
						new_key = true;
						break;
					}
				}

				if (!new_key) {

					std::cout << "# Terminal.execute: Key with name \"" + i.substr(1, i.size() - 1) + "\" doesn't exist!\n";
					curr_k = Key::getNullKey();
				}
			}
			else curr_a.push_back(i);
		}
		if (data[curr_k]) data[curr_k]->execute(curr_a);
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

	virtual void execute(Args opts) override {
	
		if (opts.size() != 2)
			std::cout << "# CenterLntr.execute: Only two arguments expected after \"-center\" key!\n";
		else {

			try {
				t->center_x = str_num(opts[0]);
				t->center_y = str_num(opts[1]);
			}
			catch (std::exception exp) {

				std::cout << exp.what() << "\n";
			}
		}
	}
};

class PointsLtnr : public Listener {

private:
	MyTerminal* t;

public:
	PointsLtnr(MyTerminal* t) : t(t) {}

	virtual void execute(Args opts) override {
	
		if (opts.size() != 1)
			std::cout << "# PointsLntr.execute: Only one argument expected after \"-points\" key!\n";
		else {

			try {
				t->points = str_num(opts[0]);
			}
			catch (std::exception exp) {

				std::cout << exp.what() << "\n";
			}
		}
	}
};

class RadiusLtnr : public Listener {

private:
	MyTerminal* t;

public:
	RadiusLtnr(MyTerminal* t) : t(t) {}

	virtual void execute(Args opts) override {
	
		if (opts.size() != 1)
			std::cout << "# RadiusLntr.execute: Only one argument expected after \"-radius\" key!\n";
		else {

			try {
				t->radius = str_num(opts[0]);
			}
			catch (std::exception exp) {

				std::cout << exp.what() << "\n";
			}
		}
	}
};

class CircleLtnr : public Listener {

private:
	MyTerminal* t;

public:
	CircleLtnr(MyTerminal* t) : t(t) {}

	virtual void execute(Args opts) override {
	
		if (!opts.empty())
			std::cout << "# CircleLntr.execute: Only keys expected after \"-circle\" key!\n";
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

	MyTerminal terminal;
	terminal.attachRoot(new RootLtnr());
	terminal.addKey(Key("center"), new CenterLtnr(&terminal));
	terminal.addKey(Key("points"), new PointsLtnr(&terminal));
	terminal.addKey(Key("radius"), new RadiusLtnr(&terminal));
	terminal.addKey(Key("xmlcrl"), new CircleLtnr(&terminal));
	
	try {
		terminal.execute(data);
	}
	catch (std::exception e) {
		std::cout << e.what() << '\n';
	}

	return 0;
}