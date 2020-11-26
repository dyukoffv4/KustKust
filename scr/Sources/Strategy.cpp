#include "../Headers/Strategy.h"
#include "../Headers/Area.h"
#include "../Headers/Player.h"
#include "../Headers/Tile.h"
#include "../Headers/TileObject.h"

Context::Context(Player* player) : player(player), strategy(nullptr) {}

Context::~Context() {

    if (strategy) delete strategy;
}

void Context::setPlayer(Player* player) {

    this->player = player;
}

void Context::setStrategy(Strategy* strategy) {

    if (strategy) delete this->strategy;
    this->strategy = strategy;
}

bool Context::mainWork() {
    
    Tile* title = Area::getArea().getTile(player->getX(), player->getY());
    if (title && title->getObj()) return false;
    this->setStrategy(nullptr);
    if (title->getObj()->getName() == APPLE) this->setStrategy(new Apple_S);
    if (title->getObj()->getName() == PIE) this->setStrategy(new Pie_S);
    if (title->getObj()->getName() == KEY) this->setStrategy(new Key_S);
    if (title->getObj()->getName() == WALL) this->setStrategy(new Wall_S);
    if (title->getObj()->getName() == EXIT) this->setStrategy(new Exit_S);
    if (strategy) return this->strategy->doWork(player, title);
    return false;
}

bool Apple_S::doWork(Player* _player, Tile* _title) {

    *_player += _title->getObj();
    Area::getArea().popTile(*_title);
    return false;
}

bool Pie_S::doWork(Player* _player, Tile* _title) {

    if (_player->getApple() >= 3 * (1 + _player->getPie())) {

        *_player += _title->getObj();
        Area::getArea().popTile(*_title);
    }
    return false;
}

bool Key_S::doWork(Player* _player, Tile* _title) {

    if (_player->getPie() >= 3) {

        *_player += _title->getObj();
        Area::getArea().popTile(*_title);
    }
    return false;
}

bool Wall_S::doWork(Player* _player, Tile* _title) {

    _player->moveBack();
    return false;
}

bool Exit_S::doWork(Player* _player, Tile* _title) {

    if (_player->getKey() > 0) return true;
    return false;
}