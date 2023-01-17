#define _USE_MATH_DEFINES
#include <cmath>
#include "terminal.hpp"
#include "utils.hpp"


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
		if (opts.size() != 2) throw std::invalid_argument("CenterLntr.execute: Only two arguments expected after \"c/center\" key!");
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
		if (opts.size() != 1) throw std::invalid_argument("PointsLntr.execute: Only one argument expected after \"p/points\" key!");
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
		if (opts.size() != 1) throw std::invalid_argument("RadiusLntr.execute: Only one argument expected after \"r/radius\" key!");
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
		if (!opts.empty()) throw std::invalid_argument("CircleLntr.execute: Only keys expected after \"-circle\" key!");
		else {
			std::string xml;
			xml += "> Circle XML: M" + num_str(t->center_x + t->radius) + " " + num_str(t->center_y) + " ";
			for (int i = 1; i < t->points; i++) {
				xml += "L";
				xml += num_str(std::cos(i / double(t->points) * M_PI * 2) * t->radius + t->center_x) + " ";
				xml += num_str(std::sin(i / double(t->points) * M_PI * 2) * t->radius + t->center_y) + " ";
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