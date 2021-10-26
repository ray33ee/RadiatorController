#include "states.h"

#include "settings.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

/* Startup state - Called once to intiate the peripherals */

void Startup::enter(FSM* fsm) {
    
    //Setup all the peripherals, LED, pins, schedule, temperature sensor, valve,
    
    //Setup the led then change the colour
    fsm->init_led();
    
    fsm->set_led_colour(255, 255, 0);
    
    
    fsm->attributes.load();
    
    //Setup the valve
    fsm->init_valve();
    
}

void Startup::update(FSM* fsm, int elapsed) {
    
    //The startup state does nothing, so we immediately move to the first state.
    
    
    fsm->next(new Off());
}

void Startup::exit(FSM* fsm) {
    
}

void Startup::led_update(int elapsed) {
    
}

#ifdef __DEBUG__
int Startup::code() {
    
    return 0;
}
#endif 

/* State to open the valve */

void On::enter(FSM* fsm) {
    
    fsm->open_valve();
    
    fsm->set_led_colour(255, 35, 0);
    
    
}

void On::update(FSM* fsm, int elapsed) {
    fsm->schedule_flags();
    fsm->schedule_state();
    
}

void On::exit(FSM* fsm) {
    
}

void On::led_update(int elapsed) {
    
}

#ifdef __DEBUG__
int On::code() {
    
    return 11;
}
#endif 

/* State to close the valve */

void Off::enter(FSM* fsm) {
    
    fsm->close_valve();
    
    fsm->set_led_colour(0, 50, 255);
    
    
}

void Off::update(FSM* fsm, int elapsed) {
    fsm->schedule_flags();
    fsm->schedule_state();
    
}

void Off::exit(FSM* fsm) {
    
}

void Off::led_update(int elapsed) {
    
}

#ifdef __DEBUG__
int Off::code() {
    
    return 10;
}
#endif 

/* Move the motor to a safe position (0) for removal/installation */

void Safe::enter(FSM* fsm) {
    
    //Disable api calls 
    fsm->enable_api(false);
    
    fsm->set_led_colour(100, 100, 100);
    
    fsm->open_valve();
    
    fsm->set_led_colour(30, 30, 30);
    
    
}

void Safe::update(FSM* fsm, int elapsed) {
    
}

void Safe::exit(FSM* fsm) {
    
}

void Safe::led_update(int elapsed) {
    
}

#ifdef __DEBUG__
int Safe::code() {
    
    return 1;
}
#endif 

/* Turn the radiator on to warm up for a predefined length of time */

Boost::Boost(int duration) {
    time_left = duration;
}

void Boost::move_previous(State* p) {
    previous = p;
}

void Boost::enter(FSM* fsm) {
    
    fsm->set_led_colour(255, 35, 0);
    
    fsm->open_valve();
    
}

void Boost::update(FSM* fsm, int elapsed) {
    
    fsm->schedule_flags();
    
    if (time_left <= 0) {
        fsm->revert();
    }
    
    time_left -= elapsed;
    
}

void Boost::led_update(int elapsed) {}

void Boost::exit(FSM* fsm) {
    
}

#ifdef __DEBUG__
int Boost::code() {
    return 20;
}
#endif 

void Descale::move_previous(State* p) {
    previous = p;
}

void Descale::enter(FSM* fsm) {
    fsm->open_valve();
    fsm->close_valve();
}

void Descale::update(FSM* fsm, int elapsed) {
    fsm->revert();
}

void Descale::led_update(int elapsed) {
    
}

void Descale::exit(FSM* fsm) {
    
}

#ifdef __DEBUG__
int Descale::code() {
    return 30;
}

#endif 



















































