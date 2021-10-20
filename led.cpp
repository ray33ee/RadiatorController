#include "led.h"

#include "Particle.h"

//Uncomment this line to enable debugging options
#define __DEBUG__

void PhotonRGB::init() {
    //Grap control of the led from the OS
    RGB.control(true);
}

void PhotonRGB::color(int r, int g, int b) {
    RGB.color(r, g, b);
}

void PhotonRGB::enable(bool e) {
    if (e) {
        RGB.brightness(255);
    } else {
        RGB.brightness(0);
    }
}
