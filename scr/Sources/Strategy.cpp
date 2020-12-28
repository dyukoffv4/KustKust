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

//

bool Context::playerWork() {

    Tile* tile = model->getPlayer()->getTile();
    tile->notify("visited by player");
    this->setStrategy(nullptr);
    if (tile->getObjs().isin(COIN)) this->setStrategy(new Coin_PS);
    if (tile->getObjs().isin(BAG)) this->setStrategy(new Bag_PS);
    if (tile->getObjs().isin(KEY)) this->setStrategy(new Key_PS);
    if (tile->getObjs().isin(WALL)) this->setStrategy(new Wall_PS);
    if (tile->getObjs().isin(EXIT)) this->setStrategy(new Exit_PS);
    if (strategy) return this->strategy->doWork(model, tile);
    return false;
}

bool Coin_PS::doWork(Model* _model, Tile* _tile) {

    List& list_t = _tile->getObjs();
    for (int i = 0; list_t[i] != nullptr; i++)
        if (list_t[i]->getName() == COIN) {

            *_model->getPlayer() += _tile->getObjs().pop(list_t[i]);
            break;
        }
    return false;
}

bool Bag_PS::doWork(Model* _model, Tile* _tile) {

    List* list_p = _model->getPlayer()->getInvent();
    int num = 0;
    for (int i = 0; (*list_p)[i] != nullptr; i++)
        if ((*list_p)[i]->getName() == COIN) num++;

    if (num >= 3) {

        int del = 3;
        for (int i = 0; (*list_p)[i] != nullptr && del; i++)
            if ((*list_p)[i]->getName() == COIN) {

                *_model->getPlayer() -= (*list_p)[i];
                i--;
                del--;
            }
    }
    else return false;

    List& list_t = _tile->getObjs();
    for (int i = 0; list_t[i] != nullptr; i++)
        if (list_t[i]->getName() == BAG) {

            *_model->getPlayer() += _tile->getObjs().pop(list_t[i]);
            break;
        }
    return false;
}

bool Key_PS::doWork(Model* _model, Tile* _tile) {

    List* list_p = _model->getPlayer()->getInvent();
    int num = 0;
    for (int i = 0; (*list_p)[i] != nullptr; i++)
        if ((*list_p)[i]->getName() == BAG) num++;

    if (num >= 3) {

        int del = 3;
        for (int i = 0; (*list_p)[i] != nullptr && del; i++)
            if ((*list_p)[i]->getName() == BAG) {

                *_model->getPlayer() -= (*list_p)[i];
                i--;
                del--;
            }
    }
    else return false;

    List& list_t = _tile->getObjs();
    for (int i = 0; list_t[i] != nullptr; i++)
        if (list_t[i]->getName() == KEY) {

            *_model->getPlayer() += _tile->getObjs().pop(list_t[i]);
            break;
        }
    return false;
}

bool Wall_PS::doWork(Model* _model, Tile* _tile) {

    _model->getPlayer()->mback();
    return false;
}

bool Exit_PS::doWork(Model* _model, Tile* _tile) {

    List* list_p = _model->getPlayer()->getInvent();
    if (list_p->isin(KEY)) return true;
    return false;
}

//

bool Context::warriorWork() {

    Tile* tile;
    for (int i = 0; (*model->getWarrs())[i] != nullptr; i++) {

        tile = (*model->getWarrs())[i]->getTile();
        tile->notify("visited by warrior");
        this->setStrategy(nullptr);
        if (tile->getObjs().isin(WALL)) this->setStrategy(new Wall_WS);
        if (strategy) this->strategy->doWork(model, tile);
    }
    return false;
}

bool Wall_WS::doWork(Model* _model, Tile* _tile) {

    for (int i = 0; _tile->getObjs()[i] != nullptr; i++)
        if (_tile->getObjs()[i]->getName() == SWAR || _tile->getObjs()[i]->getName() == RWAR)
            _tile->getObjs()[i]->mback();
    return false;
}