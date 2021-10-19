#ifndef FSM_H
#define FSM_H

#include "states.h"
#include "temperature.h"
#include "valve.h"
#include "Particle.h"

class State;
class Valve;

class FSM {
private:
    
    State* current;
    State* previous;
    
    Valve* v;
    
public:

    FSM();
    
    /* FSM functions */
    
    //Load the first state (Startup)
    void start();
    
    //Advance FSM to a new state
    void next(State* state);
    
    //Revert to the previous state
    void revert();
    
    //Call this function within the main loop, passing the time elapsed since the last call
    void update(int elapsed);
    
    /* RGB LED functions */
    
    //Initialise LED
    void init_led();
    
    //Set colour
    void set_led_colour(int r, int g, int b);
    
    /* Valve functions */
    
    //Valve startup
    void init_valve();
    
    //Fully open valve
    int open_valve();
    
    //Fully close valve
    int close_valve();
    
};

#endif 