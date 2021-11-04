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
    virtual LEDStatus* led_status() = 0;
    
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
    LEDStatus* led_status();
    void exit(FSM* fsm);
    int code();
    String name() { return String("Startup"); }
};

class Off: public State {
    static const int RGB_COLOUR = 0x000032FF;
    
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    LEDStatus* led_status();
    void exit(FSM* fsm);
    int code();
    String name() { return String("Off"); }
};


class Safe: public State {
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    LEDStatus* led_status();
    void exit(FSM* fsm);
    int code();
    String name() { return String("Safe"); }
};

class Boost: public State {
private:
    int time_left;
    bool nested;
    
public:
    static const int RGB_COLOUR = 0x00ff2300;
    Boost(int duration);
    int remaining();
    void move_previous(State* p);
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    LEDStatus* led_status();
    void exit(FSM* fsm);
    int code();
    String name() { return String("Boost"); }
};

class Descale: public State {
public:
    void move_previous(State* p);
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    LEDStatus* led_status();
    void exit(FSM* fsm);
    int code();
    String name() { return String("Descale"); }
};


class Regulate: public State {
private:
    int _last_check;
    
public:
    static const int RGB_COLOUR = 0x00ff2300;
    
    Regulate();
    void enter(FSM* fsm);
    void update(FSM* fsm, int elapsed);
    LEDStatus* led_status();
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
    LEDStatus* led_status();
    void exit(FSM* fsm);
    int code();
    String name() { return String("Panic"); }
};

class PanicStatus: public LEDStatus {
public:
    explicit PanicStatus(int code) :
        LEDStatus(LED_PATTERN_CUSTOM, LED_PRIORITY_IMPORTANT),
        _ticks(0),
        _code(code) {
    }

protected:
    virtual void update(system_tick_t ticks) override {
        // Change status color every 300 milliseconds
        _ticks += ticks;
        
        
        
        if (_ticks > _code * 400 + 1500) {
            _ticks = 0;
            return;
        }
        
        if (_ticks % 400 < 300 || _ticks > _code * 400) {
            setColor(0x00000000);
        } else {
            setColor(0x00FF0000);
        }
    }

private:
    system_tick_t _ticks;
    int _code;
};

#endif