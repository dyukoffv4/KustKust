#include "../lib/terminal.hpp"
#include "utils.hpp"
#include "paint.hpp"


namespace Listeners {
	std::vector<Paint::Image> images(1);
	std::string save_path;

	void set_load_image_path(Args opts) {
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

	void set_save_image_path(Args opts) {
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
				i = Paint::set_component(Paint::Component{opts[0][0], str_int(opts[1])}, i);
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(Arg("Listeners::set_component->") + exp.what());
		}
	}

	void put_circle(Args opts) {
		if (opts.size() != 3) throw std::invalid_argument("Listeners::put_cirlce: Only three arguments expected after \"c/circle\" key!");
		try {
			for (auto& i : images)
				i = Paint::put_circle(Paint::Circle{str_int(opts[0]), str_int(opts[1]), str_int(opts[2])}, i);
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(Arg("Listeners::execute->") + exp.what());
		}
	}

	void put_rectangle(Args opts) {
		if (opts.size() != 6) throw std::invalid_argument("Listeners::put_rectangle: Only six arguments expected after \"s/square\" key!");
		try {
			for (auto& i : images)
				i = Paint::put_rectangle(Paint::Rectangle{str_int(opts[0]), str_int(opts[1]), str_int(opts[2]), str_int(opts[3]), str_int(opts[4]), str_int(opts[5])}, i);
		}
		catch (std::domain_error exp) {
			throw std::invalid_argument(Arg("Listeners::execute->") + exp.what());
		}
	}

	void cut_the_crap(Args opts) {
		if (opts.size() != 2) throw std::invalid_argument("Listeners::set_component: Only two arguments expected after \"s/slice\" key!");
		try {
			for (auto& i : Paint::cut_the_crap(Paint::CutLines{str_int(opts[0]), str_int(opts[1])}, images[0])) images.push_back(i);
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
		terminal.setRoot(Listeners::set_load_image_path);
		terminal.setKey(Key('o', "out"), Listeners::set_save_image_path);
		terminal.setKey(Key('c', "color"), Listeners::set_component);
		terminal.setKey(Key('r', "circle"), Listeners::put_circle);
		terminal.setKey(Key('x', "slice"), Listeners::cut_the_crap);
		terminal.setKey(Key('s', "square"), Listeners::put_rectangle);
		terminal.execute(data);

		if (Listeners::images.size() == 1) Listeners::images[0].save(Listeners::save_path + ".bmp");
		else for (int i = 0; i < Listeners::images.size(); i++) Listeners::images[i].save(Listeners::save_path + dub_str(i) + ".bmp");
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << "\n";
	}

	return 0;
}