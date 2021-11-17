#include "states.h"

#include "settings.h"
#include "Particle.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

/* Startup state - Called once to intiate the peripherals */

void Startup::enter(FSM* fsm) {
    
    //Setup all the peripherals, LED, pins, schedule, temperature sensor, valve,
    LEDStatus led = LEDStatus(RGB_COLOR_YELLOW);
    
    led.setActive(true);
    
    fsm->attributes.load();
    
    //Setup the valve
    fsm->init_valve();
    
    //Setup the temperature sensor
    fsm->sensor_open();
    
    led.setActive(false);
    
}

void Startup::update(FSM* fsm, int elapsed) {
    
#ifndef __DEBUG__
    if (fsm->max_position() > 55) {
        //No Valve
        fsm->next(new Panic(1, String("No valve detected. Make sure controller is fitted properly.")));
        return;
    }
#endif
    
    /*
    if (fsm->max_position() < 5) {
        //Plunger stuck
        fsm->next(new Panic(2, String("Plunger only moved a small amount before over-current detection kicked in. (This happens occasionally, please fix. In meantime just reset the device until it works)")));
        return;
    }*/
    
    //Change to the state according to the schedule
    fsm->schedule_state();
}

void Startup::exit(FSM* fsm) {
    
}


LEDStatus* Startup::led_status() {
    //STARTUP never updates (it immediately changes to the first state
    return new LEDStatus();
}

int Startup::code() {
    
    return 0;
}

/* State to open the valve */

/*void On::enter(FSM* fsm) {
    
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
}*/

/* State to close the valve */
void Off::enter(FSM* fsm) {
    
    
    LEDStatus led = LEDStatus(RGB_COLOUR);
    
    led.setActive(true);
    
    fsm->close_valve();
    
    
    led.setActive(false);
    
    
}

void Off::update(FSM* fsm, int elapsed) {
    fsm->schedule_flags();
    fsm->schedule_state();
    
}

void Off::exit(FSM* fsm) {
    
}

LEDStatus* Off::led_status() {
   return new  LEDStatus(RGB_COLOUR, LED_PATTERN_FADE);
}

int Off::code() {
    
    return 10;
}

/* Move the motor to a safe position (0) for removal/installation */

void Safe::enter(FSM* fsm) {
    
    //Disable api calls 
    fsm->enable_api(false);
    
    LEDStatus led = LEDStatus(RGB_COLOR_WHITE);
    
    led.setActive(true);
    
    fsm->open_valve();
    
    led.setActive(false);
    
    
}

void Safe::update(FSM* fsm, int elapsed) {
    
}

void Safe::exit(FSM* fsm) {
    
}

LEDStatus* Safe::led_status() {
    return new LEDStatus(RGB_COLOR_GRAY, LED_PATTERN_FADE);
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
    nested = previous->code() == code();
}

void Boost::enter(FSM* fsm) {

    LEDStatus led = LEDStatus(RGB_COLOUR);
    
    led.setActive(true);
    
    fsm->open_valve();
    
    led.setActive(false);
    
    
}

void Boost::update(FSM* fsm, int elapsed) {
    
    if (nested) {
        fsm->revert();
    }
    
    fsm->schedule_flags();
    fsm->check_open_window();
    
    if (time_left <= 0) {
        fsm->revert();
    }
    
    time_left -= elapsed;
    
}

int Boost::remaining() {
    return time_left / 1000;
}

LEDStatus* Boost::led_status() {
    return new LEDStatus(RGB_COLOUR, LED_PATTERN_FADE);
}

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
    
    
    LEDStatus led = LEDStatus(RGB_COLOR_GREEN);
    
    led.setActive(true);
    
    fsm->open_valve();
    fsm->close_valve();
    
    led.setActive(false);
}

void Descale::update(FSM* fsm, int elapsed) {
    fsm->revert();
}

LEDStatus* Descale::led_status() {
    //DESCALE never updates (it reverts immediately during first update) so this led status does nothing
    return new LEDStatus();
}

void Descale::exit(FSM* fsm) {
    
}

int Descale::code() {
    return 30;
}

/* Automatically regulate the temperature */

Regulate::Regulate(): _last_check(0) {
    
}

void Regulate::enter(FSM* fsm) {

    LEDStatus led = LEDStatus(RGB_COLOUR);
    
    led.setActive(true);
    
    fsm->schedule_flags();
    
    int quart = Time.minute() / 15;
    int index = (Time.weekday()-1) * 24 * 4 + Time.hour() * 4 + quart;
    
    float temperature = fsm->attributes.get_entry_temperature(index);
    
    float actual_temperature = fsm->temperature();
    
    if (actual_temperature < temperature) {
        fsm->open_valve();
    } else {
        fsm->close_valve();
    }
    
    _last_check = System.millis();
    
    led.setActive(false);
    
}

void Regulate::update(FSM* fsm, int elapsed) {
    fsm->schedule_flags();
    fsm->schedule_state();
    fsm->check_open_window();
    
    
    
    if (System.millis() - _last_check > 10000) {
        int quart = Time.minute() / 15;
        int index = (Time.weekday()-1) * 24 * 4 + Time.hour() * 4 + quart;
        
        float temperature = fsm->attributes.get_entry_temperature(index);
        
        float actual_temperature = fsm->temperature();
        
        //Activate if temperature is less than schedule temperature-1
        if (actual_temperature < (temperature - 1.0f)) {
            fsm->open_valve();
        }
        
        //Deactivate if temperatureis greater than schedule temperature
        if (actual_temperature > temperature) {
            fsm->close_valve();
        }
        
        //A gap  of 1 degreemeans that small fluctuations in the temperature readings will not result in rapid on/off cycles for the motor
        
        _last_check = System.millis();
    }
    
    
    
}

LEDStatus* Regulate::led_status() {
    return new LEDStatus(RGB_COLOUR, LED_PATTERN_FADE);
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
    
    fsm->enable_api(false);
}

void Panic::update(FSM* fsm, int elapsed) {
    
}

LEDStatus* Panic::led_status() {
    return new PanicStatus(_code);
}

void Panic::exit(FSM* fsm) {
    
}

int Panic::code() {
    return -1;
}















































