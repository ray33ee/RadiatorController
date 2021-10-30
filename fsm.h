#ifndef FSM_H
#define FSM_H

#include "states.h"
#include "temperature.h"
#include "valve.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

#include "settings.h"

class State;
class Valve;
class RGB_Base;

class FSM {
private:
    
    State* current;
    
    Valve* v;
    
    //RGB_Base* rgb;
    LEDStatus led;
    
    bool api_enabled;
    
    bool api_dark; 
    
    TemperatureSensor* sensor;
    
public:
    
    Settings attributes;
    
    int initial_free_memory;

    FSM();
    
    /* FSM functions */
    
    //Load the first state (Startup)
    void start();
    
    //Advance FSM to a new state
    void next(State* state);
    
    //Revert to the desired state
    void revert();
    
    State* get_current() { return current; }
    
    void panic(int code, String message);
    
    //Call this function within the main loop, passing the time elapsed since the last call
    void update(int elapsed);
    
    void schedule_state();
    
    void schedule_flags();
    
    void check_open_window();
    
    /* Cloud API access */
    
    void enable_api(bool e);
    
    bool enable_api();
    
    void api_dark_mode(bool e);
    
    /* Temperature sensor */
    
    void sensor_open();
    
    float temperature();
    
    /* Valve functions */
    
    //Valve startup
    void init_valve();
    
    //Fully open valve
    int open_valve();
    
    //Fully close valve
    int close_valve();
    
#ifdef __DEBUG__
    //Get the position of the motor
    int position();
    
    //Get the max position of the motor
    int max_position();
    
    //Get the state code of the current state
    int current_code();
    
    bool descale() {
        //Get current time, convert to schedule index
        int quart = Time.minute() / 15;
        int index = (Time.weekday()-1) * 24 * 4 + Time.hour() * 4 + quart;
        
        //Get current entry
        Entry current_entry = attributes.get_entry(index);
        
        return current_entry.get_descale();
    }
#endif
    
};

#endif 