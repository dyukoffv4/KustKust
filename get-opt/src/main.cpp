#include "lib/terminal.hpp"
#include "utils/utils.hpp"
#include "paint.hpp"


// class CenterLtnr : public Listener {
// public:
// 	CenterLtnr(Terminal* term) : Listener(term) {}

// 	virtual Listener* getCopy() {
// 		return new CenterLtnr(term);
// 	}

// 	virtual void execute(Args opts) override {
// 		if (opts.size() != 2) throw std::invalid_argument("CenterLntr.execute: Only two arguments expected after \"c/center\" key!");
// 		try {
// 			term->Data("center_x") = opts[0];
// 			term->Data("center_y") = opts[1];
// 		}
// 		catch (std::domain_error exp) {
// 			throw std::invalid_argument(Arg("CenterLntr.execute->") + exp.what());
// 		}
// 	}
// };

// main

int main(int argc, char* argv[]) {
	// Args data;
	// for (int i = 0; i < argc; i++) data.push_back(argv[i]);

	// try {
	// 	Terminal terminal;
	// 	// terminal.Data("points") = "10";
	// 	// terminal.setKey(Key("center"), new CenterLtnr(&terminal));
	// 	terminal.execute(data);
	// }
	// catch (std::invalid_argument e) {
	// 	std::cout << e.what() << "\n";
	// }

	Paint::Image image1, image2;

	std::cout << image1.load("pict/simpsonsvr.bmp") << std::endl;
	image2 = Paint::set_component(Paint::Component{'g', 0}, image1);
	std::cout << image2.save("pict/test.bmp") << std::endl;

	return 0;
}