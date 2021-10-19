#include "states.h"

void Startup::enter(FSM* fsm) {
    //Setup all the peripherals, LED, pins, schedule, temperature sensor, valve,
    
    //Setup the led then change the colour
    fsm->init_led();
    
    fsm->set_led_colour(255, 128, 0);
    
    //Setup the valve
    fsm->init_valve();
    
    fsm->next(new TestState());
    
}

void Startup::update(FSM* fsm, int elapsed) {
    
}

void Startup::exit(FSM* fsm) {
    
}


void TestState::enter(FSM* fsm) {
    
    fsm->set_led_colour(255, 255, 255);
    
    fsm->close_valve();
    
    
}

void TestState::update(FSM* fsm, int elapsed) {
    
}

void TestState::exit(FSM* fsm) {
    
}