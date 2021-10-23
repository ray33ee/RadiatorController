#include "fsm.h"
#include "valve.h"


//Uncomment this line to enable debugging options
#define __DEBUG__

FSM::FSM() {
    current = nullptr;
    v = nullptr;
    rgb = new PhotonRGB();
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
        
    
    //Move the current state into the next state (so the next state can restore it if needed)
    state->move_previous(current);

    //Call the enter function on the new state        
    state->enter(this);
    
    //Update the current state
    current = state;
}

//Advance FSM to the current state's revert state
void FSM::revert() {
        
    //Get the state to revert to
    State* prev = current->take_previous();
    
    //Call the exit function on the current state
    if (current != nullptr)
        current->exit(this);
        
    
    //Call the enter of the state to revert to
    prev->enter(this);
    
    //Delete the current state. Since we moved the previous state out earlier, this will literally only delete the current state
    delete current;
    
    //Update the current state
    current = prev;
    
    
}
    
//Call this function within the main loop, passing the time elapsed since the last call
void FSM::update(int elapsed) {
    
    current->led_update(elapsed);
    current->update(this, elapsed);
}

/* RGB LED functions */

//Initialise LED
void FSM::init_led() {
    
    rgb->init();
}

//Set colour
void FSM::set_led_colour(int r, int g, int b) {
    
    rgb->color(r, g, b);
    
}

//Enable or disable the led
void FSM::set_led_enabled(bool e) {
    
    rgb->enable(e);
    
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

#ifdef __DEBUG__
int FSM::position() {
    return v->position();
}

int FSM::max_position() {
    return v->max_position();
}

int FSM::current_code() {
    return current->code();
}
#endif



















