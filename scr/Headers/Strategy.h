#pragma once

#include "Def.h"

class Strategy {

public:
    virtual ~Strategy() {}
    virtual bool doWork(Player*, Title*) = 0;
};

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

class Apple_S : public Strategy {

public:
    bool doWork(Player*, Title*);
};

class Pie_S : public Strategy {

public:
    bool doWork(Player*, Title*);
};

class Key_S : public Strategy {

public:
    bool doWork(Player*, Title*);
};

class Wall_S : public Strategy {

public:
    bool doWork(Player*, Title*);
};

class Exit_S : public Strategy {

public:
    bool doWork(Player*, Title*);
};