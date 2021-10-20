#ifndef STATES_H
#define STATES_H

#include "fsm.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

class FSM;

class State {
public:

    //Called when the FSM starts this state
    virtual void enter(FSM* fsm) = 0;
    
    //Called when the FSM calls update, part of main control loop
    virtual void update(FSM* fsm, int elapsed) = 0;
    
    //Called when FSM calls update, used to change LED colour
    virtual void led_update(int elapsed) = 0;
    
    //Called before the state changes to a new one
    virtual void exit(FSM* fsm) = 0;
    
#ifdef __DEBUG__
    
    //Each state must return a code to uniquely identify it (-1 is reserved for no state)
    virtual int code() = 0;
#endif    
    
    
};


class Startup: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
#ifdef __DEBUG__
    int code();
#endif 
};


class On: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
#ifdef __DEBUG__
    int code();
#endif 
};


class Off: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
#ifdef __DEBUG__
    int code();
#endif 
};


class Safe: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
#ifdef __DEBUG__
    int code();
#endif 
};

#endif