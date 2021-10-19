#ifndef STATES_H
#define STATES_H

#include "fsm.h"

class FSM;

class State {
public:

    virtual void enter(FSM* fsm) = 0;
    virtual void update(FSM* fsm, int elapsed) = 0;
    virtual void exit(FSM* fsm) = 0;
    
};


class Startup: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void exit(FSM* fsm);
};


class TestState: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void exit(FSM* fsm);
};

#endif