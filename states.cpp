#include "states.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

/* Startup state - Called once to intiate the peripherals */

void Startup::enter(FSM* fsm) {
    //Setup all the peripherals, LED, pins, schedule, temperature sensor, valve,
    
    //Setup the led then change the colour
    fsm->init_led();
    
    
    fsm->set_led_colour(255, 255, 0);
    
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
    
    fsm->set_led_colour(255, 35, 0);
    
    fsm->open_valve();
    
    
}

void On::update(FSM* fsm, int elapsed) {
    
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
    
    fsm->set_led_colour(0, 50, 255);
    
    fsm->close_valve();
    
    
}

void Off::update(FSM* fsm, int elapsed) {
    
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
























































