#include "../Headers/Controller.h"
#include "../Headers/Model.h"
#include "../Headers/View.h"

int main() {

	Model model;
	View view;
	Controller control(&model, &view);

	control.looping();

	return 0;
}