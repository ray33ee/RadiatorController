// This #include statement was automatically added by the Particle IDE.
#include "led.h"

// This #include statement was automatically added by the Particle IDE.
#include "fsm.h"
#include "states.h"
#include "valve.h"
#include "temperature.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

FSM* fsm;

// Used to keep track of time between loop() calls
long start = 0;

void setup() {
    
    fsm = new FSM();
    
    fsm->start();
    
    Particle.function("set_state", api_state);
    
#ifdef __DEBUG__
    Particle.function("position", api_position);
    Particle.function("max_position", api_max_position);
    Particle.function("get_state", api_get_state);
#endif
    
    Particle.function("test", api_test);
    
    
}

int api_test(String input) {
    return -1;
}

#ifdef __DEBUG__
int api_position(String command) {
    return fsm->position();
}

int api_max_position(String command) {
    return fsm->max_position();
}

int api_get_state(String command) {
    return fsm->current_code();
}
#endif

int api_state(String state) {
    if (state == "") {
        return -1;
    } else {
        if (state == "startup") {
            fsm->next(new Startup());
        } else if (state == "on") {
            fsm->next(new On());
        } else if (state == "off") {
            fsm->next(new Off());
        } else if (state == "safe") {
            fsm->next(new Safe());
        } else {
            return -2;
        }
        
        return 0;
    }
}


void loop() {
    
    int duration;
    
    duration = System.millis() - start;
    
    fsm->update(duration);
    
    start =  System.millis();
    
}