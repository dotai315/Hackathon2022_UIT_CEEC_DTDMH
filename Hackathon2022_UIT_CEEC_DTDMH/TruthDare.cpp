#include "TruthDare.h"

TruthDare::TruthDare()
{
    this->truthDare = false;
}

void TruthDare::begin(int button1, int button2)
{
    this->button1 = button1;
    this->button2 = button2;
}

void TruthDare::start()
{
    Serial.println("Start Truth Or Dare Game");
    pinMode(this->button1, INPUT);
    pinMode(this->button2, INPUT);
}

void TruthDare::play(mp3 mplayer)
{
    Serial.println("Truth Or Dare????");
    int button1State;
    int button2State;
    while (true)
    {
        button1State = digitalRead(this->button1);
        button2State = digitalRead(this->button2);
        if (!button1State || !button2State)
        {
            break;
        }
    }
    if (!button1State)
    {
        Serial.println("Truth");
        mplayer.play_random_mp3("truth_or_dare/dare/Track001.mp3", 6);
    }
    else 
    {
        Serial.println("Dare");
        mplayer.play_random_mp3("truth_or_dare/truth/Track001.mp3", 7);
    }
}

void TruthDare::end()
{
    this->button1 = -1;
    this->button2 = -1;
}
