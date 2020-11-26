#include "../Headers/Controller.h"
#include "../Headers/Player.h"
#include "../Headers/Area.h"
#include "../Headers/Strategy.h"
#include "../Headers/View.h"
#include "../Headers/Model.h"
#include "../Headers/Command.h"

Controller::Controller(Model* _model, View* _view) {

	this->model = _model;
	this->view = _view;
	this->key_p = false;
}

void Controller::getEvent() {

	sf::Event event;
	Command* command = nullptr;

	while (view->pollEvent(event)) {

		if (event.type == sf::Event::Closed) view->close();
		if (event.type == sf::Event::KeyPressed && !key_p) {

			if (event.key.code == sf::Keyboard::W) command = new PlayerMove_C(model, UP);
			if (event.key.code == sf::Keyboard::S) command = new PlayerMove_C(model, DOWN);
			if (event.key.code == sf::Keyboard::A) command = new PlayerMove_C(model, LEFT);
			if (event.key.code == sf::Keyboard::D) command = new PlayerMove_C(model, RIGHT);

			if (event.key.code == sf::Keyboard::Escape) command = new GamePause_C(model);

			key_p = true;
		}
		if (event.type == sf::Event::KeyReleased) key_p = false;

		if (command) {

			command->execute();
			delete command;
			command = nullptr;
		}
	}
}

void Controller::looping() {

	while (view->isOpen() && !model->game_end) {

		this->getEvent();
		view->winDraw(model->getPlayer(), model->getArea());
	}
}