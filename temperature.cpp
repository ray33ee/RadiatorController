#include "temperature.h"
#include "stdint.h"
#include "Particle.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

BME280::BME280() {
    
}

int BME280::open() {
    
    return 0;
}

float BME280::temperature() {
    
    return -1.0f;
}



AM2302::AM2302(): _last_sample_time(0), _last_temperature(-1337.0) {
    
}

int AM2302::open() {
    
    //Not strictly needed, but we set the pin as an input to protect it
    pinMode(DATA_PIN, INPUT);
    
    return 0;
}

float AM2302::temperature() {
    
    //If the time since the last sample is larger than 3 seconds (2 second delay imposed by the AM2302 spec), then we can take a temperature. If its not, use the stored value
    if (System.millis() - _last_sample_time > 3000) {
        
        //Clear the data output
        uint64_t data = 0;
        
        _last_sample_time = System.millis();
        
        //Set the pin to output
        pinMode(DATA_PIN, OUTPUT);
        
        //Pull the pin low, wait 5ms, then let go. This represents the MCU start signal
        digitalWrite(DATA_PIN, LOW);
        delay(5);
        
        //Set the pin to an input (this will also pull the voltage back up to VCC)
        pinMode(DATA_PIN, INPUT);
        
        //Wait for the sensor to pull low
        while (digitalRead(DATA_PIN) == HIGH);
        
        //The first high pulse from the sensor before the transmission stream
        pulseIn(DATA_PIN, HIGH);
        
        for (int i = 0; i < 40; ++i) {
            int length = pulseIn(DATA_PIN, HIGH);
            data <<= 1;
            data |= length > 50;
        }
        
        //Cast data to array of bytes using beautiful C magic
        char* bytes = (char*)&data;
        
        char sum = bytes[1] + bytes[2] + bytes[3] + bytes[4];
        char checksum = bytes[0];
        
        if (sum != checksum) {
            //If the checksum failed, just use the stored temperature. 
            return _last_temperature;
        }
        
        int int_temperature = (data >> 8) & 0xffff;
        
        _last_temperature = (float)int_temperature / 10.0f;
        
    } else {
        //If we cannot request a temperature because the last one was less than 3 seconds ago, just use the stored temperature
    }
    
    return _last_temperature;
}