#include "../Headers/Strategy.h"
#include "../Headers/Area.h"
#include "../Headers/Model.h"
#include "../Headers/Tile.h"
#include "../Headers/TileObject.h"
#include "../List.h"

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

bool Context::mainWork() {
    
    Tile* tile = model->getArea()->getTile(model->getPlr()->getX(), model->getPlr()->getY());
    if (!tile->getThg()) return false;

    this->setStrategy(nullptr);

    if (tile->getThg()->getName() == COIN) this->setStrategy(new Coin_S);
    if (tile->getThg()->getName() == BAG) this->setStrategy(new Bag_S);
    if (tile->getThg()->getName() == KEY) this->setStrategy(new Key_S);
    if (tile->getThg()->getName() == WALL) this->setStrategy(new Wall_S);
    if (tile->getThg()->getName() == EXIT) this->setStrategy(new Exit_S);

    if (strategy) return this->strategy->doWork(model, tile);
    return false;
}

//-------------------------------//

bool Coin_S::doWork(Model* model, Tile* tile) {

    *(dynamic_cast<Player_O*>(model->getPlr())) << tile->getThg();
    tile->setThg(nullptr);
    return false;
}

bool Bag_S::doWork(Model* model, Tile* tile) {

    int num = 0;
    List list = *model->getPlr()->getInvent();
    for (int i = 0; list[i]; i++)
        if (list[i]->getName() == COIN) num++;
    
    if (num > 2) {

        for (int i = 0; i < num; i++)
            *(dynamic_cast<Player_O*>(model->getPlr())) > * (tile->getThg());

        *(dynamic_cast<Player_O*>(model->getPlr())) << tile->getThg();
        tile->setThg(nullptr);
    }
    return false;
}

bool Key_S::doWork(Model* model, Tile* tile) {

    int num = 0;
    List list = *model->getPlr()->getInvent();
    for (int i = 0; list[i]; i++)
        if (list[i]->getName() == BAG) num++;

    if (num > 2) {

        for (int i = 0; i < num; i++)
            *(dynamic_cast<Player_O*>(model->getPlr())) > * (tile->getThg());

        *(dynamic_cast<Player_O*>(model->getPlr())) << tile->getThg();
        tile->setThg(nullptr);
    }
    return false;
}

bool Wall_S::doWork(Model* model, Tile* tile) {

    (model->getPlr())->moveBack();
    return false;
}

bool Exit_S::doWork(Model* model, Tile* tile) {

    int num = 0;
    List list = *model->getPlr()->getInvent();
    for (int i = 0; list[i]; i++)
        if (list[i]->getName() == KEY) num++;

    if (num) return true;
    return false;
}