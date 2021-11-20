// This #include statement was automatically added by the Particle IDE.
#include "fsm.h"
#include "states.h"
#include "valve.h"
#include "temperature.h"
#include "dst.h"
#include "settings.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

FSM* fsm;

DST dst;

// Used to keep track of time between loop() calls
long start = 0;

//Define custom reset reasons
const uint32_t RESET_REASON_DATA_API_FUNCTION = 1;

void external_led(uint8_t r, uint8_t g, uint8_t b) {
    analogWrite(WKP, 255-r);
    analogWrite(A4, 255-g);
    analogWrite(D2, 255-b);
}

void setup() {
    System.enableFeature(FEATURE_RESET_INFO);
    
    
    pinMode(WKP, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(D2, OUTPUT);
    
    RGB.onChange(external_led); 
    
    
    fsm = new FSM();
    
    fsm->start();
    
    
    Particle.function("led", api_led);
    Particle.function("set_state", api_state);
    
    Particle.function("dark_mode", api_temp_dark);
    
    Particle.function("modify_schedule", api_modify_schedule);
    Particle.function("copy_day", api_copy_day);
    
    Particle.function("modify_attributes", api_modify_attributes);
    
    Particle.function("modify_flags", api_modify_flags);
    
    Particle.function("default_temperature", default_temperature);
    
    Particle.function("test_push", api_push);
    Particle.function("test_retract", api_retract);
    
    Particle.variable("boost_remaining", boost_remaining);
    
    Particle.variable("flags", flags);
    
    Particle.variable("temperature", get_temperature);
    Particle.variable("initial_free_memory", fsm->initial_free_memory);
    Particle.variable("current_free_memory", System.freeMemory);
    Particle.variable("uptime", System.uptime);
    Particle.variable("time", time_string);
    Particle.variable("reset_reason", reset_reason);
    Particle.variable("reset_reason_data", reset_data);
    Particle.variable("get_attributes", get_attributes);
    
    Particle.variable("panic_code", get_error_code);
    Particle.variable("panic_message", get_error_message);
    
#ifdef __DEBUG__
    Particle.variable("position", api_position);
    Particle.variable("max_position", api_max_position);
    Particle.variable("get_state", api_get_state);
#endif
    
    Particle.function("test", api_test);
    
    Particle.function("learn", api_learn);
    
    
    fsm->initial_free_memory = System.freeMemory();
    
}

int api_push(String command) {
    return fsm->test_push(command.toInt());
}

int api_retract(String command) {
    return fsm->test_retract(command.toInt());
}

int api_learn(String command) {
    return fsm->learn_test();
}

int api_led(String command) {
    //RRR GGG BBB
    
    RGB.control(true);
    
    RGB.color(command.substring(0, 3).toInt(), command.substring(4, 7).toInt(), command.substring(8, 11).toInt());
    
    return 0;
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

int default_temperature(String command) {
    fsm->attributes.set_default_temperature(command.toFloat());
    fsm->attributes.save();
    return 0;
}

int boost_remaining() {
    Boost* casted_current = (Boost*)(fsm->get_current());
    
    if (fsm->current_code() == 20) {
        return casted_current->remaining();
    } else {
        return 0;
    }
}

int api_modify_flags(String command) {
    
    fsm->attributes.set_flags(command.toInt());
    
    
    fsm->attributes.save();
    
    return 0;
    
}

int flags() {
    return fsm->attributes.get_flags();
}

String time_string() {
    time_t local = Time.now();
    return Time.format(local, TIME_FORMAT_DEFAULT);
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
    
    if (from == to) {
        return -1;
    }
    
    if (from > 6 || to > 6) {
        return -2;
    }
    
    fsm->attributes.copy_day(from, to);
    return 0;
}

int api_modify_attributes(String command) {
    
    int breaks[3];
    
    int count = 0;
    
    for (int i = 0; i < command.length(); ++i) {
        if (command[i] == ' ') {
            breaks[count] = i;
            count++;
        }
    }
    
    if (count != 3) {
        return -1;
    }
    
    int open_window_durtation = command.substring(0, breaks[0]).toInt();
    
    float offset_temperature = command.substring(breaks[0] + 1, breaks[1]).toFloat();
    
    int short_boost = command.substring(breaks[1] + 1, breaks[2]).toInt();
    
    int long_boost = command.substring(breaks[2] + 1, breaks[3]).toInt();
    
    
    
    fsm->attributes.set_open_window_duration(open_window_durtation);
    fsm->attributes.set_offset_temperature(offset_temperature);
    fsm->attributes.set_short_boost_duration(short_boost);
    fsm->attributes.set_long_boost_duration(long_boost);
    
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

String api_get_state() {
    return fsm->state_name();
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
                fsm->next(new Boost(fsm->attributes.get_short_boost_duration() * 60000));
            } else if (state == "long") {
                fsm->next(new Boost(fsm->attributes.get_long_boost_duration() * 60000));
            } else if (state == "cancel") {
                if (fsm->current_code() == 20) {
                    fsm->revert();
                }
            } else if (state == "reset") {
                System.reset(RESET_REASON_DATA_API_FUNCTION);
            } else if (state == "safemode") {
                System.enterSafeMode();
            } else if (state == "dfu") {
                System.dfu(false);
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
    
    //Sync the time with the cloud at 1 every day
    //Check http://worldtimeapi.org/api/ip for DST at 1am and 2am every day
    
    if (Time.second() == 0 ) {
        //Wait a second so we dont send more than one response between seconds 0-1
        delay(1000);
        
        //Make a request
        dst.send();
        
        //Also once a day sync the time with the particle cloud
        if (Time.hour() == 0) {
            Particle.syncTime();
        }
    }
    
    int r = dst.recv();
    
    if (r != -1) {
        if (r == 1) {
            Time.beginDST();
        } else {
            Time.endDST();
        }
    }
    
    fsm->update(duration);
    
    start =  System.millis();
    
}