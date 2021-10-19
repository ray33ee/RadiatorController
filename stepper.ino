// This #include statement was automatically added by the Particle IDE.
#include "fsm.h"
#include "states.h"
#include "valve.h"
#include "temperature.h"

FSM* fsm;

void setup() {
    
    fsm = new FSM();
    
    fsm->start();
    
    
    Particle.function("open", api_open);
    Particle.function("close", api_close);
    
    Particle.function("test", api_test);
    
    
}

int api_open(String blocks) {
    
    return fsm->open_valve();
    
    
    
}

int api_close(String blocks) {
    
    return fsm->close_valve();
    
    
    
}

int api_test(String input) {
    return -1;
}


void loop() {
    
    
    
}