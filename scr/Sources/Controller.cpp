#include "../Headers/Controller.h"
#include "../Headers/Area.h"
#include "../Headers/Strategy.h"
#include "../Headers/View.h"
#include "../Headers/Model.h"
#include "../Headers/Command.h"
#include "../Headers/State.h"

Controller::Controller(Model* _model, View* _view) {

	this->model = _model;
	this->view = _view;
	this->command = nullptr;
}

void Controller::getEvent() {

	sf::Event event;
	if (command) {

		delete command;
		command = nullptr;
	}

	while (view->pollEvent(event)) {

		if (event.type == sf::Event::Closed) view->close();
		if (event.type == sf::Event::KeyPressed) {

			if (event.key.code == sf::Keyboard::W) command = new PlayerMove_C(model, UP);
			if (event.key.code == sf::Keyboard::S) command = new PlayerMove_C(model, DOWN);
			if (event.key.code == sf::Keyboard::A) command = new PlayerMove_C(model, LEFT);
			if (event.key.code == sf::Keyboard::D) command = new PlayerMove_C(model, RIGHT);

			if (event.key.code == sf::Keyboard::Escape) command = new GamePause_C(model);
		}
	}
}

void Controller::looping() {

	view->resize(model);

	bool step = false;

	while (view->isOpen() && !model->game_end) {

		this->getEvent();

		if (command) {

			step = !step;
			if (step) model->setState(new PlrStepState(model));
			else model->setState(new WarStepState(model));
			command->execute();
		}

		view->areaDraw(model);
		view->statDraw(model);
		if (model->isPause()) view->pauseDraw(model);
		view->display();
	}
}