#define _USE_MATH_DEFINES
#include <cmath>
#include "terminal.hpp"
#include "utils.hpp"


class RootLtnr : public Listener {
public:
	RootLtnr(Terminal* term) : Listener(term) {}

	virtual Listener* getCopy() {
		return new RootLtnr(term);
	}

	virtual void execute(Args opts) override {
		std::cout << "> Root arguments: ";
		for (auto& i : opts) std::cout << "\"" + i + "\", ";
		std::cout << ".\n";
	}
};

class CenterLtnr : public Listener {
public:
	CenterLtnr(Terminal* term) : Listener(term) {}

	virtual Listener* getCopy() {
		return new CenterLtnr(term);
	}

	virtual void execute(Args opts) override {
		if (opts.size() != 2) throw std::invalid_argument("CenterLntr.execute: Only two arguments expected after \"c/center\" key!");
		try {
			term->setData("center_x", str_num(opts[0]));
			term->setData("center_y", str_num(opts[1]));
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(Arg("CenterLntr.execute->") + exp.what());
		}
	}
};

class PointsLtnr : public Listener {
public:
	PointsLtnr(Terminal* term) : Listener(term) {}

	virtual Listener* getCopy() {
		return new PointsLtnr(term);
	}

	virtual void execute(Args opts) override {
		if (opts.size() != 1) throw std::invalid_argument("PointsLntr.execute: Only one argument expected after \"p/points\" key!");
		else {
			try {
				term->setData("points", str_num(opts[0]));
			}
			catch (std::exception exp) {
				throw std::invalid_argument(Arg("PointsLntr.execute->") + exp.what());
			}
		}
	}
};

class RadiusLtnr : public Listener {
public:
	RadiusLtnr(Terminal* term) : Listener(term) {}

	virtual Listener* getCopy() {
		return new RadiusLtnr(term);
	}

	virtual void execute(Args opts) override {
		if (opts.size() != 1) throw std::invalid_argument("RadiusLntr.execute: Only one argument expected after \"r/radius\" key!");
		else {
			try {
				term->setData("radius", str_num(opts[0]));
			}
			catch (std::exception exp) {
				throw std::invalid_argument(Arg("RadiusLntr.execute->") + exp.what());
			}
		}
	}
};

class CircleLtnr : public Listener {
public:
	CircleLtnr(Terminal* term) : Listener(term) {}

	virtual Listener* getCopy() {
		return new CircleLtnr(term);
	}

	virtual void execute(Args opts) override {
		if (!opts.empty()) throw std::invalid_argument("CircleLntr.execute: Only keys expected after \"-circle\" key!");
		else {
			int center_x(term->getData("center_x")), center_y(term->getData("center_y")), points(term->getData("points")), radius(term->getData("radius"));
			std::string xml;
			xml += "> Circle XML: M" + num_str(center_x + radius) + " " + num_str(center_y) + " ";
			for (int i = 1; i < points; i++) {
				xml += "L";
				xml += num_str(std::cos(i / double(points) * M_PI * 2) * radius + center_x) + " ";
				xml += num_str(std::sin(i / double(points) * M_PI * 2) * radius + center_y) + " ";
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
		Terminal terminal;
		terminal.setData("points", 10);
		terminal.setData("radius", 1);
		terminal.setData("center_x", 0);
		terminal.setData("center_y", 0);
		terminal.attachRoot(new RootLtnr(&terminal));
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