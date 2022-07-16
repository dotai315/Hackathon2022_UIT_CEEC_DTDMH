#pragma once 
#include "Arduino.h"
#include <ShiftRegister74HC595.h>

class FasterClick
{
private:
    int button1;
    int button2;
    int countP1;
    int countP2;
public:
    FasterClick();
    void begin(int button1, int button2);
    void start();
    void play();
    void end();
    ~FasterClick() {}
};