#include "../Headers/Command.h"
#include "../Headers/Player.h"

PlrMove_C::PlrMove_C(Player* _receiver) : receiver(_receiver) {}

void PlrMove_C::execute() {

	int ch = _getch();
	if (ch == 224) ch = _getch();
	switch (ch) {
	case 72:
		receiver->Move(UP);
		break;
	case 80:
		receiver->Move(DOWN);
		break;
	case 75:
		receiver->Move(LEFT);
		break;
	case 77:
		receiver->Move(RIGHT);
		break;
	}
}