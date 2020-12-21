#include "../Headers/Strategy.h"
#include "../Headers/Area.h"
#include "../Headers/Model.h"
#include "../Headers/Tile.h"
#include "../Headers/TileObject.h"

Context::Context(Model* _model) : model(_model), strategy(nullptr) {}

Context::~Context() {

    if (strategy) delete strategy;
}

void Context::setModel(Model* _model) {

    this->model = _model;
}

void Context::setStrategy(Strategy* _strategy) {

    if (strategy) delete this->strategy;
    this->strategy = _strategy;
}

bool Context::playerWork() {

    Tile* tile = model->getPlayer()->getTile();
    tile->notify("visited by player");
    this->setStrategy(nullptr);
    if (tile->getObjs().isin(COIN)) this->setStrategy(new Coin_S);
    if (tile->getObjs().isin(BAG)) this->setStrategy(new Bag_S);
    if (tile->getObjs().isin(KEY)) this->setStrategy(new Key_S);
    if (tile->getObjs().isin(WALL)) this->setStrategy(new Wall_S);
    if (tile->getObjs().isin(EXIT)) this->setStrategy(new Exit_S);
    if (strategy) return this->strategy->doWork(model, tile);
    return false;
}

//

bool Coin_S::doWork(Model* _model, Tile* _tile) {

    List& list = _tile->getObjs();
    for (int i = 0; list[i] != nullptr; i++)
        if (list[i]->getName() == COIN) {

            *_model->getPlayer() += list[i];
            _tile->getObjs().pop(list[i]);
            break;
        }
    return false;
}

bool Bag_S::doWork(Model* _model, Tile* _tile) {

    List& list = _tile->getObjs();
    int num = 0;
    for (int i = 0; list[i] != nullptr; i++)
        if (list[i]->getName() == COIN) num++;

    if (num >= 3) {

        for (int i = 0; list[i] != nullptr; i++)
            if (list[i]->getName() == COIN)
                *_model->getPlayer() -= list[i];
    }

    for (int i = 0; list[i] != nullptr; i++)
        if (list[i]->getName() == BAG) {

            *_model->getPlayer() += list[i];
            _tile->getObjs().pop(list[i]);
            break;
        }
    return false;
}

bool Key_S::doWork(Model* _model, Tile* _tile) {

    List& list = _tile->getObjs();
    int num = 0;
    for (int i = 0; list[i] != nullptr; i++)
        if (list[i]->getName() == BAG) num++;

    if (num >= 3) {

        for (int i = 0; list[i] != nullptr; i++)
            if (list[i]->getName() == BAG)
                *_model->getPlayer() -= list[i];
    }

    for (int i = 0; list[i] != nullptr; i++)
        if (list[i]->getName() == KEY) {

            *_model->getPlayer() += list[i];
            _tile->getObjs().pop(list[i]);
            break;
        }
    return false;
}

bool Wall_S::doWork(Model* _model, Tile* _tile) {

    _model->getPlayer()->mback();
    return false;
}

bool Exit_S::doWork(Model* _model, Tile* _tile) {

    List& list = _tile->getObjs();
    int num = 0;
    for (int i = 0; list[i] != nullptr; i++)
        if (list[i]->getName() == KEY) num++;

    if (num >= 1) return true;
    return false;
}