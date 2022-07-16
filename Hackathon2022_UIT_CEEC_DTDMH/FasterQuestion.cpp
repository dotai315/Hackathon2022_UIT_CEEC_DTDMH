#include "FasterQuestion.h"
int value,digit1,digit2,digit3,digit4;


uint8_t  numberB[] = {B11000000, //0
                      B11111001, //1 
                      B10100100, //2
                      B10110000, //3 
                      B10011001, //4
                      B10010010, //5
                      B10000011, //6
                      B11111000, //7
                      B10000000, //8
                      B10011000 //9
                     };
static ShiftRegister74HC595 sr (4,A3, A4, A5); 

void displayLed74HC595(int number)
{
    //Split number to digits:
    digit4= (number / 1000);
    digit3= (number / 100) % 10;
    digit2= (number / 10) % 10 ;
    digit1= number % 10 ;
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {numberB[digit1],numberB[digit2],numberB[digit3],numberB[digit4]};
    sr.setAll(numberToPrint); 
    //Reset them for next time
    digit3=0;
    digit4=0;
    digit1=0;
    digit2=0;
}

void FasterQuestionGame::begin(int button1, int button2, int button3)
{
    this->button1 = button1;
    this->button2 = button2;
    this->button3 = button3;
    button1StateP1 = 0; 
    button3StateP2 = 0;
    lastButton1StateP1 = 0;
    lastButton3StateP2 = 0;
    scoreP1 = 0; 
    scoreP2 = 0;
    bothDone = false; 
    gameOn = false;
    startButtonState = LOW; 
    p1Done = false;
    p2Done = false; 
    welcomeMsg = false;
}

void FasterQuestionGame::start(){
  Serial.println("Start!!!!!");
  delay(500);
  gameOn = true; // Declare a game currently running
  startTime = millis();
  while(p1Done == false || p2Done == false){
    button1StateP1 = digitalRead(button1);
    button3StateP2 = digitalRead(button3);
    // Listen for Player 1 button to be pressed and set Player 1 as done.
    if (button1StateP1 == LOW && p1Done == false) {
      while(!digitalRead(button1));
      endTimeP1 = millis();
      p1Done = true;     
    }
    // Listen for Player 2 button to be pressed and set Player 2 as done.
    if (button3StateP2 == LOW && p2Done == false) {
      while(!digitalRead(button3));
      endTimeP2 = millis();
      p2Done = true;  
    }
  }
}

void FasterQuestionGame::end(){
  finalTimeP1 = (endTimeP1 - startTime); //Calculate how long it took Player to push their button
  finalTimeP2 = (endTimeP2 - startTime); //Calculate how long it took Player to push their button
  Serial.print("P1 time:"); 
  Serial.println(finalTimeP1/1000); // Display Player 1's final time in seconds
  Serial.print("P2 time:");
  Serial.println(finalTimeP2/1000); // Display Player 2's final time in seconds

  int previousTime;
  int countTime = 0;
  Serial.println("Waiting");
  while(digitalRead(button2));
  Serial.println("Waiting next");
  while(!digitalRead(button2))
  {
    countTime++;
    delay(100);
  }
  Serial.print("Press in: ");
  Serial.println(countTime);
  if (countTime > 40)
  { 
    if (endTimeP1 < endTimeP2){ // Run if Player 1 won the round
      winningTime = (endTimeP2 - startTime) - (endTimeP1 - startTime);
      scoreP1 = scoreP1 + 1;
      Serial.print("P1 won by:");
      Serial.println(winningTime/1000);
    }
    else{
      Serial.print("P2 won by:"); // Run if Player 2 won te round
      winningTime = (endTimeP1 - startTime) - (endTimeP2 - startTime);
      scoreP2 = scoreP2 + 1;
      Serial.println(winningTime/1000);
    }
  }
  else
  {
    Serial.println("No one have score");
  }
  delay(1000);
  // Reset all variables to restart the game
  button1StateP1 = 0;
  button3StateP2 = 0; 
  lastButton1StateP1 = 0; 
  lastButton3StateP2 = 0; 
  bothDone = false;
  gameOn = false;
  startButtonState = LOW;
  p1Done = false;
  p2Done = false;
  randomTime = 0;
  startTime = 0;
  endTimeP1 = 0;
  endTimeP2 = 0;
  finalTimeP1 = 0;
  finalTimeP2 = 0;
  winningTime = 0;
  welcomeMsg = false;
}

void FasterQuestionGame::play()
{
  int numDisplay = 0;
  while (1)
  {
    // Print a welcome message, the current player's score, and set that the welcome message has been displayed
    if (welcomeMsg == false)
    {
      Serial.println(" ");
      Serial.println("Press the start button to begin");
      Serial.println("Scoreboard:");
      Serial.print("Player 1 - ");
      numDisplay = scoreP1 * 100;
      Serial.println(scoreP1);
      Serial.print("Player 2 - ");
      Serial.println(scoreP2);
      numDisplay += scoreP2;
      displayLed74HC595(numDisplay);
      welcomeMsg = true;
    } 
  
    // if the start button has been pressed and there is no game already running, begin the game
    if (gameOn == false)
    {
        Serial.println(" ");
        Serial.println("Get ready!");;
        delay(2000);
        this->start();
        this->end();
    }
  }
}
