#include "../Headers/Controller.h"
#include "../Headers/Model.h"
#include "../Headers/View.h"

int WinMain() {

	Model model;
	View view;
	Controller control(&model, &view);

	control.looping();

	return 0;
}