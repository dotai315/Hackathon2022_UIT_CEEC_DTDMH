#pragma once

#include "Arduino.h"
#include "mp3.h"

class TruthDare
{
private:
    boolean truthDare;
    int button1;
    int button2;
public:
    TruthDare();
    ~TruthDare(){}
    void begin(int button1, int button2);
    void start();
    void play(mp3 mplayer);
    void end();
};
