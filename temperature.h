#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "stdint.h"
#include "Particle.h"


//Uncomment this line to enable debugging options
#define __DEBUG__

class TemperatureSensor {
    
public:

    //Called to initialise the sensor, pins, and any other startup code
    virtual int open() = 0;
    
    //Take a reading and return the temperature
    virtual float temperature() = 0; 
  
};

class BME280: public TemperatureSensor {
    
public:

    BME280();
    
    int open();
    
    float temperature();
    
};

class AM2302: public TemperatureSensor {
    
private:
    uint64_t _last_sample_time; //Last time the temperature was taken. Given in milliseconds since device was last reset. See System.millis() for more info
    float _last_temperature;
    
    const int DATA_PIN = D6;
    
    
    
public:

    AM2302();
    
    int open();
    
    float temperature();
    
};

#endif