#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

class TemperatureSensor {
    
public:

    TemperatureSensor();

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

#endif