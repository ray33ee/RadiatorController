#ifndef STATES_H
#define STATES_H

#include "fsm.h"
#include "Particle.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

class FSM;

class State {
protected:
    State* previous;
    
public:

    //If we have no reasonable previous value, or the previous value has been deleted, it should be set to nullptr (to avoid double deletions)
    State() {
        previous = nullptr;
    }
    
    //Handle the moved previous. Most states dont need to store the previous state, so default behaviour is to delete.
    //For states that do need to restore (and therefor store) a previous state, replace with { previous = p; }
    virtual void move_previous(State* p) {
        delete p;
    }
    
    //Return the stored previous state, and replace with null
    State* take_previous() { State* tmp = previous; previous = nullptr; return tmp; }

    //Called when the FSM starts this state
    virtual void enter(FSM* fsm) = 0;
    
    //Called when the FSM calls update, part of main control loop
    virtual void update(FSM* fsm, int elapsed) = 0;
    
    //Called when FSM calls update, used to change LED colour
    virtual void led_update(int elapsed) = 0;
    
    //Called before the state changes to a new one
    virtual void exit(FSM* fsm) = 0;
    
    virtual ~State() {
        delete previous;
    }
    
    //Each state must return a code to uniquely identify it (-1 is reserved for no state)
    virtual int code() = 0;
    
    virtual String name() = 0;
    
    
};


class Startup: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
    int code();
    String name() { return String("Startup"); }
};


class On: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
    int code();
    String name() { return String("On"); }
};


class Off: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
    int code();
    String name() { return String("Off"); }
};


class Safe: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
    int code();
    String name() { return String("Safe"); }
};

class Boost: public State {
private:
    int time_left;
    
public:
    Boost(int duration);
    void move_previous(State* p);
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
    int code();
    String name() { return String("Boost"); }
};

class Descale: public State {
public:
    void move_previous(State* p);
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
    int code();
    String name() { return String("Descale"); }
};


class Regulate: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
    int code();
    String name() { return String("Regulate"); }
};


class Panic: public State {
private:
    int _code;
    String _message;
    
public:
    Panic(int code, String message);
    int get_code() { return _code; }
    String get_message() { return _message; }
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    void led_update(int elapsed);
    void exit(FSM* fsm);
    int code();
    String name() { return String("Panic"); }
};



#endif