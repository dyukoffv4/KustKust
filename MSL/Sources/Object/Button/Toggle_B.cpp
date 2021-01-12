#include "../../../Headers/Object/Button/Toggle_B.h"
#include "../../../Headers/Image/Image.h"

mgl::Toggle_B::Toggle_B(rect r, int i, Image* i_l) : Button(r, i, i_l) {}

char mgl::Toggle_B::getName() {

	return TOG_B;
}

bool mgl::Toggle_B::getSignal() {

	return click;
}