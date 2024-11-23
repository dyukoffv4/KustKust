#include <keyparser/parser.hpp>
#include <keyparser/binds.hpp>
#include "paint.hpp"

using namespace keyparser;

// Other

int atoi(std::string str) {
	int num = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] < 48 || str[i] > 57) throw std::domain_error("Invalid number format: " + str + "!");
		num = num * 10 + (str[i] - 48);
	}
	return num;
}

class help_error : public std::runtime_error {
public:
	help_error() : runtime_error(":D") {}
};

// Callback functions

namespace Root {
	std::vector<Paint::Image> images(1);
	std::string img_filepath;

	void root(const Args& opts) {
		img_filepath = opts[0];
		images[0].load(img_filepath);
	}

	void help(const Args& opts) {
		std::cout << "Input:\t<filename> [--save, --help, -c (--color), -r (--round), -x (--slice), -s (--square)]\n";
		std::cout << "Options:\n";
		std::cout << "\t--save:\tFilepath to save.\n";
		std::cout << "\t--help:\tShow help message.\n";
		std::cout << "\t-c (--color):\tChange value or RGB component.\n";
		std::cout << "\t-r (--round):\tDraw sircle.\n";
		std::cout << "\t-x (--slice):\tSlice current image into many.\n";
		std::cout << "\t-s (--square):\tCopy and paste rectangle area.\n";
		throw help_error();
	}

	void save(const Args& opts) {
		try {
			std::string path = opts.empty() ? img_filepath : opts[0];
			if (path.substr(path.size() - 4) == ".bmp") path.erase(path.size() - 4);
			
			for (int i = 0; i < images.size(); i++) {
				std::string number;
				for (int j = i + 1; j > 0; j /= 10) number = char(j % 10 + 48) + number;
				images[i].save(path + "-" + number + ".bmp");
			}
		}
		catch (std::runtime_error e) {
			throw std::invalid_argument(e.what());
		}
	}
}

namespace Color {
	void root(const Args& opts) {
		try {
			char index = opts[0][0], value = atoi(opts[1]);
			for (auto &i : Root::images) i = Paint::set_component(i, index, value);
		}
		catch (std::invalid_argument e) {
			throw std::invalid_argument(e.what());
		}
		catch (std::domain_error e) {
			throw std::invalid_argument(e.what());
		}
	}

	void help(const Args& opts) {
		std::cout << "Справочная информация по -c / --color:\n";
		std::cout << "Обязательные параметры:\n";
		std::cout << "\t1 параметр - изменяемый компонент.\n";
		std::cout << "\t2 параметр - новое значение компонента (от 0 до 255).\n";
		throw help_error();
	}
}

namespace Round {
	Paint::BGR fill_color, border_color = {0, 0, 0};
	int border_thick = 0;

	void root(const Args& opts) {
		try {
			int x = atoi(opts[0]), y = atoi(opts[1]), radius = atoi(opts[2]);
			for (auto &i : Root::images) i = Paint::put_circle(i, x, y, radius, fill_color, border_thick, border_color);
		}
		catch (std::invalid_argument exp) {
			throw std::invalid_argument(std::string("Circle->") + exp.what());
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(std::string("Circle->") + exp.what());
		}
	}

	void fill(const Args& opts) {
		try {
			fill_color.r = atoi(opts[0]);
			fill_color.g = atoi(opts[1]);
			fill_color.b = atoi(opts[2]);
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(std::string("Circle->") + exp.what());
		}
	}

	void border(const Args& opts) {
		try {
			border_thick = atoi(opts[0]);
			border_color.r = atoi(opts[1]);
			border_color.g = atoi(opts[2]);
			border_color.b = atoi(opts[3]);
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(std::string("Circle->") + exp.what());
		}
	}

	void help(const Args& opts) {
		std::cout << "Справочная информация по -r (--circle):\n";
		std::cout << "Флаги:\n";
		std::cout << "\t-f (--fill):\t\n";
		std::cout << "\t-b (--border):\t\n";
		std::cout << "Обязательные параметры:\t\n";
		std::cout << "\tФлаг -f (--fill): параметры - RGB компонент: <r> <g> <b>.\n";
		std::cout << "\t1 параметр - положение центра по горизонтали.\n";
		std::cout << "\t2 параметр - положение центра по вертикали.\n";
		std::cout << "\t3 параметр - радиус окружности.\n";
		std::cout << "Необязательные параметры:\t\n";
		std::cout << "\tФлаг -b (--border): параметры - ширина края и RGB компонент: <border> <r> <g> <b>.\n";
		throw help_error();
	}
}

namespace Slice {
	void root(const Args& opts) {
		try {
			int x_lines = atoi(opts[0]), y_lines = atoi(opts[1]);
			for (auto &i : Paint::slice_image(Root::images[0], x_lines, y_lines)) Root::images.push_back(i);
			Root::images.erase(Root::images.begin());
		}
		catch (std::invalid_argument exp) {
			throw std::invalid_argument(std::string("Slice->") + exp.what());
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(std::string("Slice->") + exp.what());
		}
	}

	void help(const Args& opts) {
		std::cout << "Справочная информация по -x / --slice:\n";
		std::cout << "Обязательные параметры:\n";
		std::cout << "\t1 параметр - число вертикальных изображений.\n";
		std::cout << "\t2 параметр - число горизонтальных изображений.\n";
		throw help_error();
	}
}

namespace Square {
	void root(const Args& opts) {
		try {
			std::vector<int> D;
			for (auto &i : opts) D.push_back(atoi(i));
			for (auto &i : Root::images) i = Paint::put_square(i, D[0], D[1], D[2], D[3], D[4], D[5]);
		}
		catch (std::invalid_argument exp) {
			throw std::invalid_argument(std::string("Square->") + exp.what());
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(std::string("Square->") + exp.what());
		}
	}

	void help(const Args& opts) {
		std::cout << "Справочная информация по -s / --square:\n";
		std::cout << "Обязательные параметры:\n";
		std::cout << "\t1 параметр - положение нижнего левого угла по горизонтали.\n";
		std::cout << "\t2 параметр - положение нижнего левого угла по вертикали.\n";
		std::cout << "\t3 параметр - положение верхнего правого угла по горизонтали.\n";
		std::cout << "\t4 параметр - положение верхнего правого угла по вертикали.\n";
		std::cout << "\t5 параметр - место по горизонтали для перемещения нижнего левого угла.\n";
		std::cout << "\t6 параметр - место по вертиакли для перемещения нижнего левого угла.\n";
		throw help_error();
	}
}

// Main function

int main(int argc, char *argv[]) {
	// Parser set up

	Parser q_parser(6);
	q_parser.addKey(Key("help"));
	
	Parser s_parser(2);
	s_parser.addKey(Key("help"));
	
	Parser r_parser(3);
	r_parser.addKey(Key("help"));
	r_parser.addKey(Key('f', "fill"), 3);
	r_parser.addKey(Key('b', "border"), 4);
	
	Parser c_parser(2);
	c_parser.addKey(Key("help"));

	Parser parser(1);
	parser.addKey(Key("help"));
	parser.addKey(Key("save"), 0, 1);
	parser.addKey(Key('c', "color"), &c_parser);
	parser.addKey(Key('r', "round"), &r_parser);
	parser.addKey(Key('s', "slice"), &s_parser);
	parser.addKey(Key('q', "square"), &q_parser);

	// Binds set up

	Binds q_binds(Square::root);
	q_binds.bind(Key("help"), Square::help, true);

	Binds s_binds(Slice::root);
	s_binds.bind(Key("help"), Slice::help, true);

	Binds r_binds(Round::root);
	r_binds.bind(Key("help"), Round::help, true);
	r_binds.bind(Key('f', "fill"), Round::fill, true);
	r_binds.bind(Key('b', "border"), Round::border, true);

	Binds c_binds(Color::root);
	c_binds.bind(Key("help"), Color::help, true);

	Binds binds(Root::root);
	binds.bind(Key("help"), Root::help, true);
	binds.bind(Key("save"), Root::save);
	binds.bind(Key('c', "color"), c_binds);
	binds.bind(Key('r', "round"), r_binds);
	binds.bind(Key('s', "slice"), s_binds);
	binds.bind(Key('q', "square"), q_binds);

	// Work

	try {
		binds.execute(parser.parse(argc, argv));
	}
	catch (help_error e) {}

	return 0;
}