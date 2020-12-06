#pragma once

#include "Defines.h"
class Model;
class Tile;

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
    Context(Model* _model);
    ~Context();

    void setModel(Model* _model);
    void setStrategy(Strategy* _strategy);
    bool mainWork();
};

///	---------------------//
//	Concrete Strategys	///

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