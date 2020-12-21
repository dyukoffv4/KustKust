#pragma once

#include "Defines.h"
class Model;
class Tile;
class View;

///	---------------------//
//	Interface Strategy	///

class Strategy {

public:
    virtual ~Strategy() {}
    virtual bool doWork(Model*, Tile*) = 0;
};

///	-----------------//
//	Cocrete Context	///

class Context {

private:
    Model* model;
    Strategy* strategy;

public:
    Context(Model*);
    ~Context();

    void setModel(Model*);
    void setStrategy(Strategy*);
    bool playerWork();
    bool warriorWork();
};

///	---------------------//
//	Concrete Strategys	///

class WarrAtt_S : public Strategy {

public:
    bool doWork(Model*, Tile*);
};

class WarrWall_S : public Strategy {

public:
    bool doWork(Model*, Tile*);
};

class Coin_S : public Strategy {

public:
    bool doWork(Model*, Tile*);
};

class Bag_S : public Strategy {

public:
    bool doWork(Model*, Tile*);
};

class Key_S : public Strategy {

public:
    bool doWork(Model*, Tile*);
};

class Wall_S : public Strategy {

public:
    bool doWork(Model*, Tile*);
};

class Exit_S : public Strategy {

public:
    bool doWork(Model*, Tile*);
};