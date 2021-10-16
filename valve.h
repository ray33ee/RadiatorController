#include "Particle.h"

//Controls low level functions of the motor and exposes functions to set the position. THis class will
// - Handle the startup sequence to learn where zero position (plunger fully retracted) and max position (valve fully closed)
// - Move the plunger to a specified position 
// - Get the position of the plunger
class Valve {
private:

    /* Magic constants */ 
    
    //Delay between coil changes (Microseconds)
    static const int STEP_DURATION = 1200;
    
    //Absolute Maximum number of blocks (form a fully retracted position) exceeding this may damage enclosure
    static const int ABSOLUTE_MAXIMUM_BLOCKS = 60;

    //If the cumulative total of all the differential pair values exceeds this value when pushing, stop the motor
    static const int PUSH_CUTOFF_TOTAL = 8000;
    
    //If the cumulative total of all the differential pair values exceeds this value when retracting, stop the motor
    static const int RETRACT_CUTOFF_TOTAL = 8000;
    
    /* Pin definitions */
    
    // Coil A
    int _a1;
    int _a2;
    
    // Coil B
    int _b1;
    int _b2;
    
    // Analog differential pair
    int _p1;
    int _p2;
    
    //Motor Enable
    int _enable;
    
    /* State variables */
    
    //Number from 0 (fully retracted) to _max_position
    int _position;
    
    //The learned maximum position
    int _max_position;
    
    /* Low level functions */
    
    //Set the driver input values
    void set_coils(int a1, int a2, int b1, int b2);

    //Deenergise coils
    void deenergise();
    
    //Initiate the delay between steps and sample the p1 and p2 voltages
    int delay_and_sample(int delay, int* cumulative);
    
    /* Mid level functions */
    
    //Push the plunger forward by n blocks. (one block is 10 cycles, or 40 steps)
    int push(int blocks);
    
    //Retract the plunger forward by n blocks. (one block is 10 cycles, or 40 steps)
    int retract(int blocks);
    
public:
    
    Valve(pin_t a1, int a2, int b1, int b2, int p1, int p2, int enable);
    
    /* High level functions */
    
    //Move to the desired positions
    int setPosition(int position);
    
    //Return the current posision
    int position() const;
    
    //Return the current posision
    int max_position() const;
    
};











































