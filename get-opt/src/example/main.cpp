#include "../lib/terminal.hpp"
#include "paint.hpp"

int str_int(std::string str) {
	int num = 0;
	if (!str.empty()) {
		bool minus = false;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '-') {
				minus = true;
				continue;
			}
			if (str[i] < 48 || str[i] > 57) throw std::domain_error("str_num: Invalid number format!");
			num = num * 10 + (str[i] - 48);
		}
		if (minus) num *= -1;
	}
	return num;
}

std::string int_str(int num) {
	std::string str;
	bool minus = (num < 0) ? true : false;
	for (int i = num; i > 0; i /= 10) str = char(i % 10 + 48) + str;
	if (num == 0) str = "0" + str;
	if (minus) str = "-" + str;
	return str;
}

namespace Listeners {
	std::vector<Paint::Image> images(1);
	std::string save_path;

	namespace Color {
		void onRoot(Args opts) {
			if (opts.size() != 2) throw std::invalid_argument("Listeners::Color: Only two arguments expected after \"c/color\" key!");
			try {
				for (auto& i : images) i = Paint::set_component(i, opts[0][0], str_int(opts[1]));
			}
			catch (std::domain_error exp) {
				throw exp;
			}
		}

		void onHelp (Args opts) {
			std::cout << "Справочная информация по -c / --color:\n";
			std::cout << "Обязательные параметры:\n";
			std::cout << "\t1 параметр - изменяемый компонент.\n";
			std::cout << "\t2 параметр - новое значение компонента (от 0 до 255).\n";
		}
	}

	namespace Circle {
		Paint::BGR fill_color, border_color = {0, 0, 0};
		int x, y, radius, border = 0;

		void onRoot(Args opts) {
			if (opts.size() != 3) throw std::invalid_argument("Listeners::Circle: Only three root arguments expected after \"r/circle\" key!");
			try {
				x = str_int(opts[0]);
				y = str_int(opts[1]);
				radius = str_int(opts[2]);
			}
			catch (std::domain_error exp) {
				throw std::invalid_argument(Arg("Listeners::Circle->") + exp.what());
			}
		}

		void onFill (Args opts) {
			if (opts.size() != 3) throw std::invalid_argument("Listeners::Circle: Only three arguments expected after \"f/fill\" key!");
			try {
				fill_color.r = str_int(opts[0]);
				fill_color.g = str_int(opts[1]);
				fill_color.b = str_int(opts[2]);
			}
			catch (std::domain_error exp) {
				throw std::invalid_argument(Arg("Listeners::Circle->") + exp.what());
			}
		}

		void onBorder (Args opts) {
			if (opts.size() != 4) throw std::invalid_argument("Listeners::Circle: Only four arguments expected after \"b/border\" key!");
			try {
				border = str_int(opts[0]);
				border_color.r = str_int(opts[1]);
				border_color.g = str_int(opts[2]);
				border_color.b = str_int(opts[3]);
			}
			catch (std::domain_error exp) {
				throw std::invalid_argument(Arg("Listeners::Circle->") + exp.what());
			}
		}

		void onHelp (Args opts) {
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
		}

		void execute() {
			try {
				for (auto& i : images) i = Paint::put_circle(i, x, y, radius, fill_color, border, border_color);
			}
			catch (std::exception exp) {
				throw std::invalid_argument(Arg("Listeners::Circle->") + exp.what());
			}
		}
	}

	namespace Slice {
		void onRoot(Args opts) {
			if (opts.size() != 2) throw std::invalid_argument("Listeners::Slice: Only two arguments expected after \"x/slice\" key!");
			try {
				for (auto& i : Paint::slice_image(images[0], str_int(opts[0]), str_int(opts[1]))) images.push_back(i);
				images.erase(images.begin());
			}
			catch (std::domain_error exp) {
				throw std::invalid_argument(Arg("Listeners::Slice->") + exp.what());
			}
		}

		void onHelp (Args opts) {
			std::cout << "Справочная информация по -x / --slice:\n";
			std::cout << "Обязательные параметры:\n";
			std::cout << "\t1 параметр - число вертикальных изображений.\n";
			std::cout << "\t2 параметр - число горизонтальных изображений.\n";
		}
	}

	namespace Square {
		void onRoot(Args opts) {
			if (opts.size() != 6) throw std::invalid_argument("Listeners::Square: Only six arguments expected after \"s/square\" key!");
			try {
				for (auto& i : images)
					i = Paint::put_square(i, str_int(opts[0]), str_int(opts[1]), str_int(opts[2]), str_int(opts[3]), str_int(opts[4]), str_int(opts[5]));
			}
			catch (std::domain_error exp) {
				throw std::invalid_argument(Arg("Listeners::Square->") + exp.what());
			}
		}

		void onHelp (Args opts) {
			std::cout << "Справочная информация по -s / --square:\n";
			std::cout << "Обязательные параметры:\n";
			std::cout << "\t1 параметр - положение нижнего левого угла по горизонтали.\n";
			std::cout << "\t2 параметр - положение нижнего левого угла по вертикали.\n";
			std::cout << "\t3 параметр - положение верхнего правого угла по горизонтали.\n";
			std::cout << "\t4 параметр - положение верхнего правого угла по вертикали.\n";
			std::cout << "\t5 параметр - место по горизонтали для перемещения нижнего левого угла.\n";
			std::cout << "\t6 параметр - место по вертиакли для перемещения нижнего левого угла.\n";
		}
	}

	namespace Main {
		void set_load_path(Args opts) {
			if (opts.size() != 2) throw std::invalid_argument("Listeners::Main: No working file specified!");
			try {
				images[0].load(opts[1]);
				save_path = opts[1];
				int pos = opts[1].find(".bmp");
				if (pos) save_path = opts[1].substr(0, pos) + "_0";
			}
			catch (std::domain_error exp) {
				throw std::invalid_argument(Arg("Listeners::Main->") + exp.what());
			}
		}

		void set_save_path(Args opts) {
			if (opts.size() != 1) throw std::invalid_argument("Listeners::Main: Only one arguments expected after \"o/out\" key!");
			try {
				save_path = opts[0];
				int pos = opts[0].find(".bmp");
				if (pos) save_path = opts[0].substr(0, pos);
			}
			catch (std::domain_error exp) {
				throw std::invalid_argument(Arg("Listeners::Main->") + exp.what());
			}
		}

		void onColor(Args opts) {
			Terminal terminal;
			terminal.setRoot(Listeners::Color::onRoot);
			terminal.setKey(Key('h', "help"), Listeners::Color::onHelp);
			terminal.execute(opts);
		}

		void onCircle(Args opts) {
			Terminal terminal;
			terminal.setRoot(Listeners::Circle::onRoot);
			terminal.setKey(Key('f', "fill"), Listeners::Circle::onFill);
			terminal.setKey(Key('b', "border"), Listeners::Circle::onBorder);
			terminal.setKey(Key('h', "help"), Listeners::Circle::onHelp);
			terminal.execute(opts);
			Listeners::Circle::execute();
		}

		void onSlice(Args opts) {
			Terminal terminal;
			terminal.setRoot(Listeners::Slice::onRoot);
			terminal.setKey(Key('h', "help"), Listeners::Slice::onHelp);
			terminal.execute(opts);
		}

		void onSquare(Args opts) {
			Terminal terminal;
			terminal.setRoot(Listeners::Square::onRoot);
			terminal.setKey(Key('h', "help"), Listeners::Square::onHelp);
			terminal.execute(opts);
		}

		void onHelp(Args opts) {
			std::cout << "Справочная информация по программе:\n";
			std::cout << "Вызов:\t<программа> <файл> [-o (--out), -c (--color), -r (--circle), -x (--slice), -s (--square), -h (--help)]\n";
			std::cout << "Флаги:\n";
			std::cout << "\t-o (--out):\tПуть и имя файла сохранения.\n";
			std::cout << "\t-c (--color):\tИзменение значения RGB компонента.\n";
			std::cout << "\t-r (--circle):\tРисование круга или круга с отверстием.\n";
			std::cout << "\t-x (--slice):\tРазрезание исходного изображение на несколько.\n";
			std::cout << "\t-s (--square):\tКопирование и перемещения части изображения в другое место.\n";
			std::cout << "\t-h (--help):\tПолучение справочной информации.\n";
		}
	}
}

int main(int argc, char* argv[]) {
	Args data;
	for (int i = 0; i < argc; i++) data.push_back(argv[i]);

	try {
		Terminal terminal;
		terminal.setRoot(Listeners::Main::set_load_path);
		terminal.setKey(Key('o', "out"), Listeners::Main::set_save_path);
		terminal.setKey(Key('c', "color"), Listeners::Main::onColor);
		terminal.setKey(Key('r', "circle"), Listeners::Main::onCircle);
		terminal.setKey(Key('x', "slice"), Listeners::Main::onSlice);
		terminal.setKey(Key('s', "square"), Listeners::Main::onSquare);
		terminal.setKey(Key('h', "help"), Listeners::Main::onHelp);
		terminal.execute(data);

		if (Listeners::images.size() == 1) Listeners::images[0].save(Listeners::save_path + ".bmp");
		else for (int i = 0; i < Listeners::images.size(); i++) Listeners::images[i].save(Listeners::save_path + int_str(i) + ".bmp");
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << "\n";
	}

	return 0;
}