#pragma once 
#include <SPI.h>
#include <FreeStack.h>

//Add the SdFat Libraries
#include <SdFat.h>

#include <vs1053_SdFat.h>

#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
#include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
#include <SimpleTimer.h>
#endif
#include <Arduino.h>
#include <ShiftRegister74HC595.h>


class FasterQuestionGame
{
private:
    int button1;
    int button2;
    int button3;
    int button1StateP1; //Player 1 button tracking
    int button3StateP2; //Player 2 button tracking
    int lastButton1StateP1; // Player 1 last button state (used to detect a button press)
    int lastButton3StateP2; // Player 2 last button state (used to detect a button press)
    int scoreP1; // Player 1 score tracking
    int scoreP2; // Player 2 score tracking
    boolean bothDone; // Used to see if both players have pressed their buttons
    boolean gameOn; // Keep track if the game is going on or not
    boolean startButtonState; // Start button initalization
    boolean p1Done; // Keep track of Player 1's button press
    boolean p2Done; // Keep track of Player 1's button press
    boolean welcomeMsg; // Keep track if the welcome message has already been displayed

    long randomTime; // Hold the random time between the start of the game and the indicator light coming back on
    long startTime; // When did the game start
    long endTimeP1; // When did Player 1 press their button
    long endTimeP2; // When did Player 2 press their button

    float finalTimeP1; // Time elapsed between start of the game and Player 1 pressing their button
    float finalTimeP2; // Time elapsed between start of the game and Player 2 pressing their button
    float winningTime; // Time between the winning and losing player's time 
public:
    FasterQuestionGame() {}
    ~FasterQuestionGame() {}
    void begin(int button1, int button2, int button3);
    void start();
    void end();
    void play(); 
};
