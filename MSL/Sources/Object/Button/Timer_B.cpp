#include "../../../Headers/Object/Button/Timer_B.h"
#include "../../../Headers/Image/Image.h"

mgl::Timer_B::Timer_B(rect r, int i, Image* i_l, short sec) : Button(r, i, i_l) {

	timer = sec * short(SEC);
	end = false;
}

char mgl::Timer_B::getName() {

	return TIM_B;
}

bool mgl::Timer_B::getSignal() {

	if (end) end = false;
	if (click && (int(clock()) > timer || int(clock()) < 0)) {

		click = false;
		end = true;
	}
	return end;
}