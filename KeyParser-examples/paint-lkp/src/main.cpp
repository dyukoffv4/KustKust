#include <lkeyparser/parser.hpp>
#include "paint.hpp"

using namespace keyparser;


// Handlers for Tasks

void color(std::vector<Paint::Image> &images, char index, char value) {
	try {
		for (auto &i : images) i = Paint::set_component(i, index, value);
	}
	catch (std::invalid_argument exp) {
		throw std::invalid_argument(std::string("Color->") + exp.what());
	}
	catch (std::domain_error exp) {
		throw std::invalid_argument(std::string("Color->") + exp.what());
	}
}

void colorHelp() {
	std::cout << "Справочная информация по -c / --color:\n";
	std::cout << "Обязательные параметры:\n";
	std::cout << "\t1 параметр - изменяемый компонент.\n";
	std::cout << "\t2 параметр - новое значение компонента (от 0 до 255).\n";
}

void round(std::vector<Paint::Image> &images, int x, int y, int r, Paint::BGR fill_color, int border = 0, Paint::BGR border_color = {0, 0, 0}) {
	try {
		for (auto &i : images) i = Paint::put_circle(i, x, y, r, fill_color, border, border_color);
	}
	catch (std::invalid_argument exp) {
		throw std::invalid_argument(std::string("Round->") + exp.what());
	}
	catch (std::domain_error exp) {
		throw std::invalid_argument(std::string("Round->") + exp.what());
	}
}

void roundHelp(Args opts) {
	std::cout << "Справочная информация по -r (--round):\n";
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
}

void slice(std::vector<Paint::Image> &images, int x_lines, int y_lines) {
	try {
		int to_erase = images.size();
		for (auto &i : images) for (auto &j : Paint::slice_image(i, x_lines, y_lines)) images.push_back(j);
		images.erase(images.begin(), images.begin() + to_erase);
	}
	catch (std::invalid_argument exp) {
		throw std::invalid_argument(std::string("Slice->") + exp.what());
	}
	catch (std::domain_error exp) {
		throw std::invalid_argument(std::string("Slice->") + exp.what());
	}
}

void sliceHelp() {
	std::cout << "Справочная информация по -x / --slice:\n";
	std::cout << "Обязательные параметры:\n";
	std::cout << "\t1 параметр - число вертикальных изображений.\n";
	std::cout << "\t2 параметр - число горизонтальных изображений.\n";
}

void squad(std::vector<Paint::Image> &images, int x0, int y0, int x1, int y1, int dx, int dy) {
	try {
		for (auto &i : images) i = Paint::put_square(i, x0, y0, x1, y1, dx, dy);
	}
	catch (std::invalid_argument exp) {
		throw std::invalid_argument(std::string("Squad->") + exp.what());
	}
	catch (std::domain_error exp) {
		throw std::invalid_argument(std::string("Squad->") + exp.what());
	}
}

void squadHelp() {
	std::cout << "Справочная информация по -q / --squad:\n";
	std::cout << "Обязательные параметры:\n";
	std::cout << "\t1 параметр - положение нижнего левого угла по горизонтали.\n";
	std::cout << "\t2 параметр - положение нижнего левого угла по вертикали.\n";
	std::cout << "\t3 параметр - положение верхнего правого угла по горизонтали.\n";
	std::cout << "\t4 параметр - положение верхнего правого угла по вертикали.\n";
	std::cout << "\t5 параметр - место по горизонтали для перемещения нижнего левого угла.\n";
	std::cout << "\t6 параметр - место по вертиакли для перемещения нижнего левого угла.\n";
}

void loadImage(std::string path, Paint::Image &image) {
	try {
		image.load(path);
	}
	catch (std::domain_error exp) {
		throw std::invalid_argument(std::string("LoadImage->") + exp.what());
	}
}

void saveImage(std::string path, std::vector<Paint::Image> &images) {
	try {
		std::string path = path.substr(0, path.find(".bmp"));
		if (images.size() == 1) images[0].save(path + ".bmp");
		else {
			for (int i = 0; i < images.size(); i++) {
				std::string str;
				for (int j = i; j > 0; j /= 10) str = char(j % 10 + 48) + str;
				images[i].save(path + str + ".bmp");
			}
		}
	}
	catch (std::domain_error exp) {
		throw std::invalid_argument(std::string("SaveImage->") + exp.what());
	}
	catch (std::invalid_argument exp) {
		throw std::invalid_argument(std::string("SaveImage->") + exp.what());
	}
}

void rootHelp() {
	std::cout << "Справочная информация по программе:\n";
	std::cout << "Вызов:\t<программа> <файл> [-s (--save), -c (--color), -r (--round), -x (--slice), -q (--squad), -h (--help)]\n";
	std::cout << "Флаги:\n";
	std::cout << "\t-s (--save):\tПуть и имя файла сохранения.\n";
	std::cout << "\t-c (--color):\tИзменение значения RGB компонента.\n";
	std::cout << "\t-r (--round):\tРисование круга или круга с отверстием.\n";
	std::cout << "\t-x (--slice):\tРазрезание исходного изображение на несколько.\n";
	std::cout << "\t-q (--squad):\tКопирование и перемещения части изображения в другое место.\n";
	std::cout << "\t-h (--help):\tПолучение справочной информации.\n";
}

// Temorary show out function

void task_print(std::ostream &out, const keyparser::Task &data, std::string offset = "") {
    out << offset << data.name.fname() << " : ";
	if (data.root.size() != 0) {
		for (auto i = data.root.begin(); i != --data.root.end(); i++) out << *i << ", ";
		out << data.root.back();
	}
	out << '\n';
    for (auto &i : data.childs) task_print(out, i.second, offset + "  ");
}

// Setting up function (MAIN)

int main(int argc, char *argv[]) {
	try {
		Parser color(2);
		color.addKey(Key('h', "help"), 0);

		Parser round(3);
		round.addKey(Key('f', "fill"), 3);
		round.addKey(Key('b', "border"), 4);
		round.addKey(Key('h', "help"), 0);

		Parser slice(2);
		slice.addKey(Key('h', "help"), 0);

		Parser squad(6);
		squad.addKey(Key('h', "help"), 0);

		Parser root(0, 1);
		root.addKey(Key('s', "save"), 0, 1);
		root.addKey(Key('c', "color"), &color);
		root.addKey(Key('r', "round"), &round);
		root.addKey(Key('x', "slice"), &slice);
		root.addKey(Key('q', "squad"), &squad);
		root.addKey(Key('h', "help"), 0);

		Task tasks = root.parse(argc, argv);

		task_print(std::cout, tasks);
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << "\n";
	}

	return 0;
}