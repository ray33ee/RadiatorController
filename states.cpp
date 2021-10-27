#include "states.h"

#include "settings.h"
#include "Particle.h"

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
    
    
#ifndef __DEBUG__
    if (fsm->max_position() > 55) {
        //No Valve
        fsm->next(new Panic(1, String("No valve detected. Make sure controller is fitted properly.")));
        return;
    }
#endif
    
    if (fsm->max_position() < 5) {
        //Plunger stuck
        fsm->next(new Panic(2, String("Plunger only moved a small amount before over-current detection kicked in. (This happens occasionally, please fix. In meantime just reset the device until it works)")));
        return;
    }
    
    //Change to the state according to the schedule
    fsm->schedule_state();
}

void Startup::exit(FSM* fsm) {
    
}

void Startup::led_update(int elapsed) {
    
}

int Startup::code() {
    
    return 0;
}

/* State to open the valve */

void On::enter(FSM* fsm) {
    
    fsm->open_valve();
    
    fsm->set_led_colour(255, 35, 0);
    
    
}

void On::update(FSM* fsm, int elapsed) {
    fsm->schedule_flags();
    fsm->schedule_state();
    fsm->check_open_window();
    
}

void On::exit(FSM* fsm) {
    
}

void On::led_update(int elapsed) {
    
}

int On::code() {
    
    return 11;
}

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

int Off::code() {
    
    return 10;
}

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

int Safe::code() {
    
    return 1;
}

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
    fsm->check_open_window();
    
    if (time_left <= 0) {
        fsm->revert();
    }
    
    time_left -= elapsed;
    
}

void Boost::led_update(int elapsed) {}

void Boost::exit(FSM* fsm) {
    
}

int Boost::code() {
    return 20;
}

/* Open and close valve to prevent valve from ceasing */

void Descale::move_previous(State* p) {
    previous = p;
}

void Descale::enter(FSM* fsm) {
    
    
    fsm->set_led_colour(0, 255, 0);
    
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

int Descale::code() {
    return 30;
}

/* Automatically regulate the temperature */

void Regulate::enter(FSM* fsm) {
    
}

void Regulate::update(FSM* fsm, int elapsed) {
    fsm->schedule_flags();
    fsm->schedule_state();
    fsm->check_open_window();
    
}

void Regulate::led_update(int elapsed) {
    
}

void Regulate::exit(FSM* fsm) {
    
}

int Regulate::code() {
    return 12;
}

/* Panic state represents an unrecoverable error */

Panic::Panic(int code, String message): _code(code), _message(message) {
    
}

void Panic::enter(FSM* fsm) {
    
    fsm->set_led_colour(255, 0, 0);
    
    fsm->enable_api(false);
}

void Panic::update(FSM* fsm, int elapsed) {
    
}

void Panic::led_update(int elapsed) {
    
}

void Panic::exit(FSM* fsm) {
    
}

int Panic::code() {
    return -1;
}















































