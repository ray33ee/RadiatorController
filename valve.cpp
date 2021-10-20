#include "valve.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

Valve::Valve(/*pin_t a1, int a2, int b1, int b2, int p1, int p2, int enable*/) {
    
    /* Initialise pins */
    
    //Setup the control pins
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D0, OUTPUT);
    
    //Enable the L293D driver
    digitalWrite(D0, HIGH);
    
    //Start the system deenergised
    deenergise();
    
    /*_a1 = a1;
    _a2 = a2;
    _b1 = b1;
    _b2 = b2;
    _p1 = p1;
    _p2 = p2;
    _enable = enable;*/
    
    /* Startup sequence */
    
    //Retract fully or until the plunger bottoms out. This garuntees that after this call, the plunger will be at position 0
    retract(ABSOLUTE_MAXIMUM_BLOCKS);
    
    //At this point progress should be zero
    _position = 0;
    
    //Push to the absolute maximum, or until the plunger stops
    push(ABSOLUTE_MAXIMUM_BLOCKS);
    
    //This position is the new maximum
    _max_position = position();
    
}

//Set the driver input values
void Valve::set_coils(int a1, int a2, int b1, int b2) {
    
    digitalWrite(D1, a1);
    digitalWrite(D2, a2);
    digitalWrite(D3, b1);
    digitalWrite(D4, b2);
    
}

void Valve::deenergise() {
    set_coils(0,0,0,0);
}

int Valve::delay_and_sample(int delay, int* cumulative) {
    int start = micros();
    
    int p1 = analogRead(A0);
    int p2 = analogRead(A1);
    int diff = p2 - p1;
    
    *cumulative += diff;

    int duration  = micros() - start;
    
    delayMicroseconds(STEP_DURATION - duration);
    
    return 0;
}

int Valve::push(int blocks) {
    
    for (int j = 0; j < blocks; ++j) {
        
        int total = 0;
        
        for (int i = 0; i < 10; ++i) {
            set_coils(1, 0, 1, 0);
            delay_and_sample(STEP_DURATION, &total);
            set_coils(0, 1, 1, 0);
            delay_and_sample(STEP_DURATION, &total);
            set_coils(0, 1, 0, 1);
            delay_and_sample(STEP_DURATION, &total);
            set_coils(1, 0, 0, 1);
            delay_and_sample(STEP_DURATION, &total);
        }
        
        if (total > PUSH_CUTOFF_TOTAL) { 
            deenergise();
            return total;   
        }
        
        _position += 1;
    }
    
    deenergise();
    return 0;
}

int Valve::retract(int blocks) {

    for (int j = 0; j < blocks; ++j) {
        
        int total = 0;
        
        for (int i = 0; i < 10; ++i) {
            set_coils(1, 0, 0, 1);
            delay_and_sample(STEP_DURATION, &total);
            set_coils(0, 1, 0, 1);
            delay_and_sample(STEP_DURATION, &total);
            set_coils(0, 1, 1, 0);
            delay_and_sample(STEP_DURATION, &total);
            set_coils(1, 0, 1, 0);
            delay_and_sample(STEP_DURATION, &total);
        }
        
        if (total > RETRACT_CUTOFF_TOTAL) { 
            deenergise();
            return total;   
        }
        
        _position -= 1;
        
    }
    
    deenergise();
    return 0;
}

    
//Move to the desired positions
int Valve::setPosition(int position) {
    //Bounds check
    if (position < 0 || position > _max_position) {
        return -1;
    } 
    
    if (position < _position) {
        
        retract(_position - position);
        
    } else if (position > _position) {
        
        push(position - _position);
        
    }
    
    return 0;
}

//Return the current posision
int Valve::position() const {
    return _position;
}

//Return the maximum position learned at startup
int Valve::max_position() const {
    return _max_position;
}

int Valve::open_valve() {
    return setPosition(0);
}

int Valve::close_valve() {
    return setPosition(_max_position);
}








































