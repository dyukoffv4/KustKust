#include "../Headers/Model.h"
#include "../Headers/Strategy.h"
#include "../Headers/Area.h"
#include "../Headers/Iterator.h"
#include "../Headers/Tile.h"
#include "../Headers/Observer.h"
#include "../Headers/Bridge.h"
#include "../Headers/State.h"

Model::Model(std::string a_path, std::string l_path)  {

	this->game_end = false;
	this->game_pause = false;
	this->area = &Area::getArea(a_path);
	if (!this->area->isGood()) this->game_end = true;
	this->player = area->getPlr();
	this->warriors = area->getWarr();

	this->context = new Context(this);
	this->observer = (Observer*)new TileObs(LOG_PATH);
	this->bridge = new Bridge(observer);
	this->state = nullptr;

	for (Iterator i = area->getIterator(); !i.iterEnd(); i++)
		i.getCurr().attach(bridge);
}

Model::~Model() {

	for (Iterator i = area->getIterator(); !i.iterEnd(); i++)
		i.getCurr().detach(bridge);

	delete context;
	delete observer;
	delete bridge;
	delete warriors;
	if (state) delete state;
}

void Model::moveAll(char direct) {

	if (game_pause) return;

	if (state) state->MakeStep(direct);

	if (context->warriorWork()) game_end = true;
	if (context->playerWork()) game_end = true;
}

void Model::swapPause() {

	game_pause = !game_pause;
}

void Model::setState(State* _state) {

	if (state) delete state;
	state = _state;
}

Object* Model::getPlayer() {

	return player;
}

List* Model::getWarrs() {

	return warriors;
}

Area* Model::getArea() {

	return area;
}

bool Model::isPause() {

	return game_pause;
}