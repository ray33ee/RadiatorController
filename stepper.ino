// This #include statement was automatically added by the Particle IDE.
#include "valve.h"

Valve* v;

void setup() {
    
    RGB.control(true);
    
    RGB.color(255, 128, 0);
    
    v = new Valve(D1, D2, D3, D4, A0, A1, D0);
    
    RGB.color(255, 255, 255);
    
    Particle.function("set_position", api_set);
    Particle.function("get_position", api_get);
    Particle.function("get_max", api_max);
    
    
}

int api_set(String blocks) {
    
    return v->setPosition(blocks.toInt());
    
}

int api_get(String arg) {
    
    return v->position();
    
}

int api_max(String arg) {
    
    return v->max_position();
    
}


void loop() {
    
    
    
}