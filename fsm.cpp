#include "fsm.h"
#include "valve.h"

FSM::FSM() {
    current = nullptr;
    previous = nullptr;
    v = nullptr;
}
    
/* FSM functions */

void FSM::start() {
    next(new Startup());
}

//Advance FSM to a new state
void FSM::next(State* state) {
    
    //Call the exit function on the current state
    if (current != nullptr)
        current->exit(this);
    
    //Call the enter function on the new state
    state->enter(this);
    
    if (previous != nullptr)
        delete previous;
    
    //Update the previous state
    previous = current;
    
    //Update the current state
    current = state;
    
    
}

//Revert to the previous state
void FSM::revert() {
    
    if (previous != nullptr) {
    
        //Call the exit function on the current state
        current->exit(this);
        
        //Call the enter function on the new state
        previous->enter(this);
        
        if (current != nullptr)
            delete current;
        
        current = previous;
        
        previous = nullptr;
    }
}
    
//Call this function within the main loop, passing the time elapsed since the last call
void FSM::update(int elapsed) {
    current->update(this, elapsed);
}

/* RGB LED functions */

//Initialise LED
void FSM::init_led() {
    RGB.control(true);
}

//Set colour
void FSM::set_led_colour(int r, int g, int b) {
    
    RGB.color(r, g, b);
    
}

/* Valve functions */

//Valve startup
void FSM::init_valve() {
    
    v = new Valve();
    
}
    
//Fully open valve
int FSM::open_valve() {
    
    return v->open_valve();
    
}

//Fully close valve
int FSM::close_valve() {
    
    return v->close_valve();
    
}