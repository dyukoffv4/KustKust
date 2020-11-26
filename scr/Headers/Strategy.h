#pragma once

#include "Defines.h"
class Player;
class Tile;
class View;

///	---------------------//
//	Interface Strategy	///

class Strategy {

public:
    virtual ~Strategy() {}
    virtual bool doWork(Player*, Tile*) = 0;
};

///	-----------------//
//	Cocrete Context	///

class Context {

private:
    Player* _player;
    Strategy* _strategy;

public:
    Context(Player* player);
    ~Context();

    void setPlayer(Player* player);
    void setStrategy(Strategy* strategy);
    bool mainWork();
};

///	---------------------//
//	Concrete Strategys	///

class Apple_S : public Strategy {

public:
    bool doWork(Player*, Tile*);
};

class Pie_S : public Strategy {

public:
    bool doWork(Player*, Tile*);
};

class Key_S : public Strategy {

public:
    bool doWork(Player*, Tile*);
};

class Wall_S : public Strategy {

public:
    bool doWork(Player*, Tile*);
};

class Exit_S : public Strategy {

public:
    bool doWork(Player*, Tile*);
};