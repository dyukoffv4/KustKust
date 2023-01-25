#include "../lib/terminal.hpp"
#include "utils.hpp"
#include "paint.hpp"

// const char help_main[] 	= "Справочная информация по K\n\n-h --help\t\tПолучение справочной информации по K\n-s --set_component\tИзменение значения компонента цвета изображения\n-c --put_circle\t\tРисование окружности\n-x --cut_file\t\tНарезка файла\n-i --input_file\t\tВвод изменяемого файла\n-o --output_file \tВвод выходного файла\n-f --file_info\t\tПолучение информации о файле\n\nКоманда не может принять более 100 команд";
// const char help_cut[] 	= "Справочная информация по -x\n\n-h --help\t\tПолучение справочной информации по -x\n-x --Xnumber\t\tПолучение числа разделений по горизонтали\n-y --Ynumber\t\tПолучение числа разделений по вертикали\n";
// const char help_color[] = "Справочная информация по -s\n\n-h --help\t\tПолучение справочной информации по -s\n-c --component\t\tУстановка изменяемого компонента\n-m --max\t\tУстановка максимального значения компонента цвета\n-n --min\t\tУстановка минимального значения компонента цвета\n";
// const char help_circ[] 	= "Справочная информация по -c\n\n-h --help\t\tПолучение справочной информации по -c\n-c --by_corners\t\tРисование круга через координаты углов\n-r --by_radius\t\tРисование окружности через координаты центра и радиус\n-w --width\t\tПолучение ширины линии окружности\n-l --line_color\t\tПолучение цвета линии окружности\n-f --fill\t\tПолучения цвета заливки окружности\n";
// const char help_corn_circ[] = "Справочная информация по -c-c\n\n-h --help\t\tПолучение справочной информации по -c-c\n-f --first\t\tВвод координат первого угла\n-s --second\t\tВвод координат второго угла\n";
// const char help_rad_circ[] 	= "Справочная информация по -c-r\n\n-h --help\t\tПолучение справочной информации по -c-r\n-c --center\t\tВвод координат центра окружности\n-r --radius\t\tВвод радиуса\n";

namespace Listeners {
	std::vector<Paint::Image> images(1);
	std::string save_path;

	void set_load_path(Args opts) {
		if (opts.size() != 2) throw std::invalid_argument("Listeners::set_load_image_path: No working file specified!");
		try {
			images[0].load(opts[1]);
			save_path = opts[1];
			int pos = opts[1].find(".bmp");
			if (pos) save_path = opts[1].substr(0, pos) + "_0";
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(Arg("Listeners::set_load_image_path->") + exp.what());
		}
	}

	void set_save_path(Args opts) {
		if (opts.size() != 1) throw std::invalid_argument("Listeners::set_save_image_path: Only one arguments expected after \"o/out\" key!");
		try {
			save_path = opts[0];
			int pos = opts[0].find(".bmp");
			if (pos) save_path = opts[0].substr(0, pos);
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(Arg("Listeners::set_save_image_path->") + exp.what());
		}
	}

	void set_component(Args opts) {
		if (opts.size() != 2) throw std::invalid_argument("Listeners::set_component: Only two arguments expected after \"c/color\" key!");
		try {
			for (auto& i : images)
				i = Paint::set_component(i, opts[0][0], str_int(opts[1]));
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(Arg("Listeners::set_component->") + exp.what());
		}
	}

	void put_circle(Args opts) {
		if (opts.size() != 3) throw std::invalid_argument("Listeners::put_cirlce: Only three arguments expected after \"c/circle\" key!");
		try {
			for (auto& i : images)
				i = Paint::put_circle(i, str_int(opts[0]), str_int(opts[1]), str_int(opts[2]), Paint::BGR{255, 255, 255}, 10);
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(Arg("Listeners::execute->") + exp.what());
		}
	}

	void put_square(Args opts) {
		if (opts.size() != 6) throw std::invalid_argument("Listeners::put_rectangle: Only six arguments expected after \"s/square\" key!");
		try {
			for (auto& i : images)
				i = Paint::put_square(i, str_int(opts[0]), str_int(opts[1]), str_int(opts[2]), str_int(opts[3]), str_int(opts[4]), str_int(opts[5]));
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(Arg("Listeners::execute->") + exp.what());
		}
	}

	void slice_image(Args opts) {
		if (opts.size() != 2) throw std::invalid_argument("Listeners::set_component: Only two arguments expected after \"s/slice\" key!");
		try {
			for (auto& i : Paint::slice_image(images[0], str_int(opts[0]), str_int(opts[1]))) images.push_back(i);
			images.erase(images.begin());
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(Arg("Listeners::execute->") + exp.what());
		}
	}
}

// main

int main(int argc, char* argv[]) {
	Args data;
	for (int i = 0; i < argc; i++) data.push_back(argv[i]);

	try {
		Terminal terminal;
		terminal.setRoot(Listeners::set_load_path);
		terminal.setKey(Key('o', "out"), Listeners::set_save_path);
		terminal.setKey(Key('c', "color"), Listeners::set_component);
		terminal.setKey(Key('r', "circle"), Listeners::put_circle);
		terminal.setKey(Key('x', "slice"), Listeners::slice_image);
		terminal.setKey(Key('s', "square"), Listeners::put_square);
		terminal.execute(data);

		if (Listeners::images.size() == 1) Listeners::images[0].save(Listeners::save_path + ".bmp");
		else for (int i = 0; i < Listeners::images.size(); i++) Listeners::images[i].save(Listeners::save_path + int_str(i) + ".bmp");
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << "\n";
	}

	return 0;
}