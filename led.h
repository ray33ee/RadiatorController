#ifndef RGB_LED_H
#define RGB_LED_H

//Uncomment this line to enable debugging options
#define __DEBUG__

class RGB_Base {
public:
    
    virtual void init() = 0;
    
    virtual void color(int r, int g, int b) = 0;
    
    virtual void enable(bool e) = 0;
    
};

//Use the Built in RGB LED on the Photon board
class PhotonRGB: public RGB_Base {
    
    void init();
    
    void color(int r, int g, int b);
    
    void enable(bool e);
    
};

//Use the external RGB in the top PCB
class TopRGB: public RGB_Base {
    
};


#endif