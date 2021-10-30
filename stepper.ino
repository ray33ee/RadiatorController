// This #include statement was automatically added by the Particle IDE.
#include "settings.h"

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

//Define custom reset reasons
const uint32_t RESET_REASON_DATA_API_FUNCTION = 1;

void setup() {
    System.enableFeature(FEATURE_RESET_INFO);
    
    fsm = new FSM();
    
    fsm->start();
    
    Particle.function("set_state", api_state);
    
    Particle.function("dark_mode", api_temp_dark);
    
    Particle.function("modify_schedule", api_modify_schedule);
    Particle.function("copy_day", api_copy_day);
    
    Particle.function("modify_attributes", api_modify_attributes);
    
    Particle.variable("temperature", get_temperature);
    Particle.variable("initial_free_memory", fsm->initial_free_memory);
    Particle.variable("current_free_memory", System.freeMemory);
    Particle.variable("uptime", System.uptime);
    Particle.variable("time", Time.now);
    Particle.variable("reset_reason", reset_reason);
    Particle.variable("reset_reason_data", reset_data);
    Particle.variable("schedule_state", schedule_state);
    Particle.variable("get_attributes", get_attributes);
    
    Particle.variable("panic_code", get_error_code);
    Particle.variable("panic_message", get_error_message);
    
#ifdef __DEBUG__
    Particle.variable("position", api_position);
    Particle.variable("max_position", api_max_position);
    Particle.variable("get_state", api_get_state);
#endif
    
    Particle.function("test", api_test);
    
    
    fsm->initial_free_memory = System.freeMemory();
    
}

String reset_reason() {
    switch (System.resetReason())
    {
        case RESET_REASON_PIN_RESET:
        	 return String("RESET_REASON_PIN_RESET");
        	break;
        case RESET_REASON_POWER_MANAGEMENT:
        	 return String("RESET_REASON_POWER_MANAGEMENT");
        	break;
        case RESET_REASON_POWER_DOWN:
        	 return String("RESET_REASON_POWER_DOWN");
        	break;
        case RESET_REASON_POWER_BROWNOUT:
        	 return String("RESET_REASON_POWER_BROWNOUT");
        	break;
        case RESET_REASON_WATCHDOG:
        	 return String("RESET_REASON_WATCHDOG");
        	break;
        case RESET_REASON_UPDATE:
        	 return String("RESET_REASON_UPDATE");
        	break;
        case RESET_REASON_UPDATE_TIMEOUT:
        	 return String("RESET_REASON_UPDATE_TIMEOUT");
        	break;
        case RESET_REASON_FACTORY_RESET:
        	 return String("RESET_REASON_FACTORY_RESET");
        	break;
        case RESET_REASON_SAFE_MODE:
        	 return String("RESET_REASON_SAFE_MODE");
        	break;
        case RESET_REASON_DFU_MODE:
        	 return String("RESET_REASON_DFU_MODE");
        	break;
        case RESET_REASON_PANIC:
        	 return String("RESET_REASON_PANIC");
        	break;
        case RESET_REASON_USER:
        	 return String("RESET_REASON_USER");
        	break;
        case RESET_REASON_UNKNOWN:
        	 return String("RESET_REASON_UNKNOWN");
        	break;
        case RESET_REASON_NONE:
        	 return String("RESET_REASON_NONE");
        	break;
        default:
            return String("UNKNOWN_RESET_REASON");
            break;
    }
    
}

int schedule_state() {
    int quart = Time.minute() / 15;
    int index = (Time.weekday()-1) * 24 * 4 + Time.hour() * 4 + quart;
    
    return fsm->attributes.get_entry(index).get_temperature(1);
}

int reset_data() {
    return System.resetReasonData();
}

int get_error_code() {
    
    //Dynamic cast doesn't seem to be supported, so we use a dodgy C style cast. We know if the cast is valid because the code for the Panic state is -1
    
    Panic* casted_current = (Panic*)(fsm->get_current());
    
    if (fsm->current_code() == -1) {
        return casted_current->get_code();
    } else {
        return 0;
    }
    
}

String get_attributes() {
    /*int get_open_window_duration() { return _ow_duration; }
    float get_offset_temperature() { return _offset_temperature / 10.f; }
    int get_short_boost_duration() { return _short_duration; }
    int get_long_boost_duration() { return _long_duration; }
    float get_default_temperature() { return _default_temperature.unpack(35.5f); }*/
    
    return String(String(fsm->attributes.get_open_window_duration()) + " " + 
        String(fsm->attributes.get_offset_temperature()) + " " + 
        String(fsm->attributes.get_short_boost_duration()) + " " + 
        String(fsm->attributes.get_long_boost_duration()) + " " + 
        String(fsm->attributes.get_default_temperature()));
}

String get_error_message() {
    
    //Dynamic cast doesn't seem to be supported, so we use a dodgy C style cast. We know if the cast is valid because the code for the Panic state is -1
    
    Panic* casted_current = (Panic*)(fsm->get_current());
    
    if (fsm->current_code() == -1) {
        return casted_current->get_message();
    } else {
        return String("Controller is not in a panic state");
    }
    
}

float get_temperature() {
    return fsm->temperature();
}

int api_copy_day(String command) {
    int from = command.substring(0, 1).toInt();
    int to = command.substring(2, 3).toInt();
    
    if (from >= to || from == to) {
        return -1;
    }
    
    if (from > 6 || to > 6) {
        return -2;
    }
    
    fsm->attributes.copy_day(from, to);
    return 0;
}

int api_modify_attributes(String command) {
    /*int get_open_window_duration() { return _ow_duration; }
    float get_offset_temperature() { return _offset_temperature / 10.f; }
    int get_short_boost_duration() { return _short_duration; }
    int get_long_boost_duration() { return _long_duration; }
    float get_default_temperature() { return _default_temperature.unpack(35.5f); }
    
    void set_open_window_duration(int value) { _ow_duration = value; }
    void set_offset_temperature(float value) { _offset_temperature = value * 10.0f; }
    void set_short_boost_duration(int value) { _short_duration = value; }
    void set_long_boost_duration(int value) { _long_duration = value; }
    void set_default_temperature(float value) { _default_temperature = PackedTemperature(value); }
    */
    
    int breaks[4];
    
    int count = 0;
    
    for (int i = 0; i < command.length(); ++i) {
        if (command[i] == ' ') {
            breaks[count] = i;
            count++;
        }
    }
    
    int open_window_durtation = command.substring(0, breaks[0]).toInt();
    
    float offset_temperature = command.substring(breaks[0] + 1, breaks[1]).toFloat();
    
    int short_boost = command.substring(breaks[1] + 1, breaks[2]).toInt();
    
    int long_boost = command.substring(breaks[2] + 1, breaks[3]).toInt();
    
    float default_temperature = command.substring(breaks[3] + 1).toFloat();
    
    
    fsm->attributes.set_open_window_duration(open_window_durtation);
    fsm->attributes.set_offset_temperature(offset_temperature);
    fsm->attributes.set_short_boost_duration(short_boost);
    fsm->attributes.set_long_boost_duration(long_boost);
    fsm->attributes.set_default_temperature(default_temperature);
    
    fsm->attributes.save();
    
    return 0;
    
}
 
int api_modify_schedule(String command) {
    //Format: SSS EEE sss tt.t d D
    //SSS three digits 000-671 representing the start time
    //EEE three digits 000-671 representing the end time
    //sss three digits 000-999 representing the state
    //tt.t three digits 10.0-35.5 representing the temperature
    //d one digit 0-1 boolean representing dark mode
    //D one digit 0-1 boolean representing a descale
    
    int start = command.substring(0, 3).toInt();
    
    if (start > 671) 
        return -2;
    
    int end = command.substring(4, 7).toInt();
    
    if (end > 672) 
        return -2;
    
    if (start >= end)
        return -1;
        
    
    int state = command.substring(8, 11).toInt();
    
    float temperature = command.substring(12, 16).toFloat();
    
    int darkmode = command.substring(17, 18).toInt();
    
    int descale = command.substring(19, 20).toInt();
    
    fsm->attributes.fill_schedule(start, end, state, temperature, darkmode, descale);
    
    return 0;
}

int api_test(String input) {
    
    int quart = Time.minute() / 15;
    int index = (Time.weekday()-1) * 24 * 4 + Time.hour() * 4 + quart;
    
    return fsm->attributes.get_default_temperature();
    return fsm->descale();
    return index;
    return fsm->attributes.get_entry(input.toInt()).get_state();
}

int api_temp_dark(String command) {
    if (command == "on") {
        fsm->api_dark_mode(true);
    } else {
        fsm->api_dark_mode(false);
    }
    return 0;
}

#ifdef __DEBUG__
int api_position() {
    return fsm->position();
}

int api_max_position() {
    return fsm->max_position();
}

int api_get_state() {
    return fsm->current_code();
}
#endif

int api_state(String state) {
    if (fsm->enable_api()) {
        if (state == "") {
            return -1;
        } else {
            if (state == "safe") {
                fsm->next(new Safe());
            } else if (state == "short") {
                fsm->next(new Boost(fsm->attributes.get_short_boost_duration()));
            } else if (state == "long") {
                fsm->next(new Boost(fsm->attributes.get_long_boost_duration()));
            } else if (state == "descale") {
                fsm->next(new Descale());
            } else if (state == "reset") {
                System.reset(RESET_REASON_DATA_API_FUNCTION);
            } else {
                return -2;
            }
            
            return 0;
        }
    } else {
        return -4;
    }
}


void loop() {
    
    int duration;
    
    
    
    duration = System.millis() - start;
    
    fsm->update(duration);
    
    start =  System.millis();
    
}