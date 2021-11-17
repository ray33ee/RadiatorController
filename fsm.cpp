#include "fsm.h"
#include "valve.h"

#include "Particle.h"
#include "settings.h"
#include "states.h"
#include "temperature.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

FSM::FSM() {
    current = nullptr;
    v = nullptr;
    api_enabled = true;
    api_dark = false;
    sensor = new Dummy();
    led = nullptr;
}

void FSM::schedule_state() {
    //Get current time, convert to schedule index
    int quart = Time.minute() / 15;
    int index = (Time.weekday()-1) * 24 * 4 + Time.hour() * 4 + quart;
    
    //Get current entry
    Entry current_entry = attributes.get_entry(index);
    
    //If the state has changed in the schedule, then load the new state
    if (current_entry.get_state() != current->code()) {
        
        //If the state is a Regualte state, get the regulation temperature
        
        switch (current_entry.get_state()) {
            case 10:
                next(new Off());
                break;
            case 12:
                next(new Regulate());
                break;
            default:
                {}
        }
        
        
    }
}

void FSM::schedule_flags() {
    //Get current time, convert to schedule index
    int quart = Time.minute() / 15;
    int index = (Time.weekday()-1) * 24 * 4 + Time.hour() * 4 + quart;
    
    //Get current entry
    Entry current_entry = attributes.get_entry(index);
    
    if (current_entry.get_descale() && Time.minute() % 15 == 2 && Time.second() == 0) {
        next(new Descale());
    }
    
    //Turn the LED On/Off depending if darkmode is off/on
    
    
    
    if ((current_entry.get_dark_mode() || api_dark) == led->isOn() && led->priority() <= LED_PRIORITY_NORMAL ) {
        //rgb->enable(!(current_entry.get_dark_mode() || api_dark));
        
        if (led->isOn()) {
            led->off();
        } else {
            led->on();
        }
        
    } 
}
    
void FSM::check_open_window() {
    //If we detect a rapid drop in temperature, change to the open window state
}

String FSM::state_name() { 
    return current->name();
}
    
/* FSM functions */

void FSM::start() {
    next(new Startup());
}

//Advance FSM to a new state
void FSM::next(State* state) {
    
    led->setActive(false);
    
    delete led;
    
    //Call the exit function on the current state
    if (current != nullptr)
        current->exit(this);
        
    
    //Move the current state into the next state (so the next state can restore it if needed)
    state->move_previous(current);
    
    Particle.publish("state", state->name());

    //Call the enter function on the new state        
    state->enter(this);
    
    led = state->led_status();
    
    led->setActive(true);
    
    //Update the current state
    current = state;
}

//Advance FSM to the current state's revert state
void FSM::revert() {
        
    //Get the state to revert to
    State* prev = current->take_previous();
    
    led->setActive(false);
    
    delete led;
    
    //Call the exit function on the current state
    if (current != nullptr)
        current->exit(this);
    
    Particle.publish("state", prev->name());
    
    //Call the enter of the state to revert to
    prev->enter(this);
    
    led = prev->led_status();
    
    led->setActive(true);
    
    //Delete the current state. Since we moved the previous state out earlier, this will literally only delete the current state
    delete current;
    
    //Update the current state
    current = prev;
    
    
}
    
//Call this function within the main loop, passing the time elapsed since the last call
void FSM::update(int elapsed) {
    
    current->update(this, elapsed);
}

void FSM::panic(int code, String message) {
    next(new Panic(code, message));
}

/* Cloud api access */

void FSM::enable_api(bool e) {
    api_enabled = e;
}

bool FSM::enable_api() {
    return api_enabled;
}
    
void FSM::api_dark_mode(bool e) {
    api_dark = e;
}
    
/* Temperature sensor */
    
void FSM::sensor_open() {
    sensor->open();
}

float FSM::temperature() {
    return sensor->temperature() + attributes.get_offset_temperature();
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



















