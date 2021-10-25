#ifndef SETTINGS_H
#define SETTINGS_H

#include <cstdint>
#include "Particle.h"

class PackedTemperature {
private: 
    uint8_t _packed;
    
public: 

    PackedTemperature() {}
    
    PackedTemperature(float temperature) {
        _packed = (uint8_t)((temperature  - 10.0f) * 10.0f);
    }

    //A packed temperature stores the temperature in the range of 10 degrees to 35.4 degrees, in 0.1 degree increments. 
    // A packed temperature of 255 represents the default temperature.
    // This function unpacks a packed temperature or used a default
    float unpack(float default_temperature) {
        return _packed != 0xff ? (float)_packed / 10.0f + 10.0f : default_temperature;
    }
    
  
    
};

//Class representing a single entry in the schedule, defining the state of the controller at this particular time
class Entry {
private: 
    

    //First byte of the entry containing various flags
    struct HalfEntry {
        uint8_t dark_mode : 1;
        uint8_t descale : 1;
    } _half_entry;
    
    uint8_t _state;
    
    PackedTemperature packed_temperature;
    
public:

    Entry() {}
    
    Entry(bool dark_mode, bool descale, uint8_t state, PackedTemperature temperature) {
        _half_entry.dark_mode = dark_mode;
        _half_entry.descale = descale;
        _state = state;
        packed_temperature = temperature;
    }
    
    //A packed temperature stores the temperature in the range of 10 degrees to 35.4 degrees, in 0.1 degree increments. 
    // A packed temperature of 255 represents the default temperature.
    // This function unpacks a packed temperature or used a default
    float get_temperature(float default_temperature) {
        return packed_temperature.unpack(default_temperature);
    }
    
    bool get_dark_mode() {
        return _half_entry.dark_mode;
    }
    
    bool get_descale() {
        return _half_entry.descale;
    }
    
    int get_state() {
        return _state;
    }
        
};

class Settings {
private:

    const uint32_t MAGIC_CONSTANT =  0xf1765b8d;

    uint32_t _magic;
    uint16_t _ow_duration;
    uint8_t _offset_temperature;
    uint16_t _short_duration;
    uint16_t _long_duration;
    uint8_t _default_temperature;
    
    Entry _schedule[672];
    
    
public:
    Settings();     
    
    int get_open_window_duration() { return _ow_duration; }
    float get_offset_temperature() { return _offset_temperature / 10.f; }
    int get_short_boost_duration() { return _short_duration; }
    int get_long_boost_duration() { return _long_duration; }
    float get_default_temperature() { return _default_temperature; }
    
    void fill_schedule() { 
        
            for (int j = 0; j < 7; ++j)
            {
                for (int i = 0; i < 24 * 4; ++i) { 
                    if (i >= 10*4 && i < 19*4) {
                        
                        _schedule[j * 24 * 4 + i] = Entry(false, false, 11, PackedTemperature(20.0f));
                    } else {
                        _schedule[j * 24 * 4 + i] = Entry(false, false, 10, PackedTemperature(20.0f));
                    }
                }
            
            }
            
            //Save to eeprom
            save();
        //}
    } 
    
    Entry get_entry(int index) { return _schedule[index]; }
    
    
    void load() {
        EEPROM.get(0, *this);
    }
    
    void save() { 
        EEPROM.put(0, *this);
    }
    
};

#endif