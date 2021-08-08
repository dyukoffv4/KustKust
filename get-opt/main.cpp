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

std::string buildCircleXML(double c_x, double c_y, double rad, int pts) {

	std::string xml;
	xml += "M" + num_str(c_x + rad) + " " + num_str(c_y) + " ";
	for (int i = 1; i < pts; i++) {

		xml += "L";
		xml += num_str(std::cos(i / double(pts) * 6.28319) * rad + c_x) + " ";
		xml += num_str(std::sin(i / double(pts) * 6.28319) * rad + c_y) + " ";
	}
	xml += "Z";
	return xml;
}

// classes

typedef std::string Key;
typedef std::string Opt;
typedef std::vector<Opt> Opts;
typedef std::vector<Key> Keys;
typedef std::pair<Key, Opts> Task;
typedef std::vector<Task> Tasks;

class GetOptions {

private:
	Tasks tasks;
	Keys keys;
	Opts data;

	void rebuildTasks() {

		bool is_key_open = false;

		tasks.clear();
		tasks.push_back(Task("", Opts()));
		for (auto& i : data) {

			if (i[0] == '-') is_key_open = false;

			if (!is_key_open) {

				for (auto& j : keys) {

					if (i.substr(1, i.size() - 1) == j) {

						is_key_open = true;
						break;
					}
				}
				if (is_key_open) {

					tasks.push_back(Task(i.substr(1, i.size() - 1), Opts()));
					continue;
				}
			}

			tasks[tasks.size() - 1].second.push_back(i);
		}
	}

public:
	void setKeys(Opts keys) {

		for (auto& i : keys)
			if (i == "") throw std::exception("# GetOptions.setKeys: Empty keys get!");
		this->keys = keys;
		rebuildTasks();
	}

	void setData(Opts data) {

		this->data = data;
		rebuildTasks();
	}

	Tasks getTasks() {

		return tasks;
	}
};

class Listener {

public:
	virtual void execute(Opts) = 0;
};

class Terminal {

private:
	std::map<Key, Listener*> data;

public:
	Terminal() {}
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
	
	void execute(Opts input) {

		Keys keys;
		for (auto& i : data) keys.push_back(i.first);
		GetOptions executer;
		try {
			executer.setKeys(keys);
			executer.setData(input);
		}
		catch (std::exception exp) {

			std::cout << exp.what() << "\n";
		}
		Tasks tasks = executer.getTasks();

		for (auto& i : tasks)
			if (data[i.first]) data[i.first]->execute(i.second);
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


class CenterLtnr : public Listener {

private:
	MyTerminal* t;

public:
	CenterLtnr(MyTerminal* t) : t(t) {}

	virtual void execute(Opts opts) override {
	
		if (opts.size() != 2)
			std::cout << "# main: Only two arguments expected after \"-center\" key!\n";
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

	virtual void execute(Opts opts) override {
	
		if (opts.size() != 1)
			std::cout << "# main: Only one argument expected after \"-points\" key!\n";
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

	virtual void execute(Opts opts) override {
	
		if (opts.size() != 1)
			std::cout << "# main: Only one argument expected after \"-radius\" key!\n";
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

	virtual void execute(Opts opts) override {
	
		if (!opts.empty())
			std::cout << "# main: Only keys expected after \"-circle\" key!\n";
		else
			std::cout << "> Circle XML: " + buildCircleXML(t->center_x, t->center_y, t->radius, t->points) + "\n";
	}
};

// main

int main(int argc, char* argv[]) {

	Opts data;
	for (int i = 0; i < argc; i++) data.push_back(argv[i]);
	
	MyTerminal terminal;
	terminal.addKey("center", new CenterLtnr(&terminal));
	terminal.addKey("points", new PointsLtnr(&terminal));
	terminal.addKey("radius", new RadiusLtnr(&terminal));
	terminal.addKey("circle", new CircleLtnr(&terminal));

	terminal.execute(data);

	return 0;
}