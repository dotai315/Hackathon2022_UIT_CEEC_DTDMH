#include "FasterQuestion.h"

#define BT_FUCNS  1
#define BT_RED    2
#define BT_GREEN  3

#define DEBUG_PRINT

enum GAME_TYPE {
  TRUTH_AND_DARE,
  WHO_FASTER_CLICK,
  WHO_FASTER_QUESTION
};

int button1 = A0;
int button2 = A1;
int button3 = A2;
int gameType = 1;
int countMode = 0;
int numberPlayer = 2;
FasterQuestionGame fq_game;
int buttonRead(void)
{
  while (1)
  {
    if (!digitalRead(button1))
    {
      while(!digitalRead(button1));
      return 1;
    }
  
    if (!digitalRead(button2))
    {
      while(!digitalRead(button2));
      return 2;
    }
    if (!digitalRead(button3))
    {
      while(!digitalRead(button3));
      return 3;
    }
  }
}

enum GAME_TYPE InitGame() 
{
  int modeGame = buttonRead();
  switch(modeGame)
  {
  case 1: 
    return TRUTH_AND_DARE;
  case 2:
    return WHO_FASTER_CLICK;
  case 3:
    return WHO_FASTER_QUESTION;
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("IU HACKATHON 2022 - LUCKY GAME BOX");
  Serial.println("Setting Button...");
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  fq_game.begin(button1, button2, button3);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(InitGame()) {
    case TRUTH_AND_DARE:
      Serial.println("TruthAndDare");
      TruthAndDare_GAME();
      break;
    case WHO_FASTER_CLICK:
      Serial.println("WhoFasterClick");
      WhoFasterClick_GAME();
      break;
    case WHO_FASTER_QUESTION:
      Serial.println("WhoFasterQuestion");
      fq_game.play();
    break;
  }

}

void TruthAndDare_GAME() {
  if (digitalRead(BT_GREEN))
  {
    countMode = 0;
    while(digitalRead(BT_GREEN))
    {
      countMode++;
      delay(300);
      if (countMode > 20)
      break;
    }
    if (countMode < 20)
    {
      // Start
    }
    else 
    {
      // Điều chỉnh số lượng người chơi
      if (digitalRead(BT_GREEN));

    }
  }
}
void WhoFasterClick_GAME() {

}
