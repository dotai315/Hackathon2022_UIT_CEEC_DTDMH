#include "mp3.h"
#include "FasterQuestion.h"
#include "FasterClick.h"
#include "TruthDare.h"
#include <Adafruit_PCF8574.h>
Adafruit_PCF8574 pcf;

#include <ShiftRegister74HC595.h>

uint8_t  numberBin[] = {B11000000, //0
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

static ShiftRegister74HC595 sr (4, A3, A4, A5);

//#define DEBUG
#define DELAY_PUSH_BT 250
#define DELAY_HOLD_BT 100

#define WIN_POINT 30

#define LED9 4
#define LED10 5

#define BT_FUCNS  1
#define BT_RED    2
#define BT_GREEN  3

#define DEBUG_PRINT

enum GAME_TYPE {
  TRUTH_AND_DARE,
  WHO_FASTER_CLICK,
  WHO_FASTER_QUESTION
};

byte score1, score2;

int button1 = A0;
int button2 = A1;
int button3 = A2;
int gameType = 1;
int countMode = 0;
int numberPlayer = 2;

int countCheck = 0;

mp3 mplayer;
FasterQuestionGame fq_game;
//FasterClick fc_game;
TruthDare td_game;

void Randon_Affect();

int buttonRead(void)
{
  while (1)
  {
    if (!digitalRead(button1))
    {
      delay(DELAY_PUSH_BT);
      while (!digitalRead(button1));
      return 1;
    }
    if (!digitalRead(button2))
    {
      delay(DELAY_PUSH_BT);
      while (!digitalRead(button2));
      return 2;
    }
    if (!digitalRead(button3))
    {
      delay(DELAY_PUSH_BT);
      while (!digitalRead(button3));
      return 3;
    }
  }
}

enum GAME_TYPE InitGame()
{
  int modeGame = buttonRead();
  switch (modeGame)
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
  //  fc_game.begin(button1, button3);
  td_game.begin(button1, button3);
  mplayer.begin();

  pinMode(LED9, OUTPUT);
  pinMode(LED10, OUTPUT);

  if (!pcf.begin(0x20, &Wire)) {
    Serial.println("Couldn't find PCF8574");
    while (1);
  }
  for (uint8_t p = 0; p < 8; p++) {
    pcf.pinMode(p, OUTPUT);
  }
  // Tắt tất cả led
  for (int i = 0; i < 8 ; i++)
    pcf.digitalWrite(i, HIGH);
  digitalWrite(LED9, HIGH);
  digitalWrite(LED10, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(3000);
  switch (InitGame()) {
    /*case TRUTH_AND_DARE:
      Serial.println("TruthAndDare");
#ifndef DEBUG
      td_game.start();
      while (1)
      {
        // Thêm hiểu ứng khởi động
        Serial.println("Is playing");

        // Điều chỉnh số lượng người chơi
        if (!digitalRead(button1))
        {
          delay(DELAY_PUSH_BT);
          countCheck = 0;
          while (!digitalRead(button1))
          {
            countCheck++;
            delay(DELAY_HOLD_BT); // 100ms
            if (countCheck > 30)
              break;
          }
          // Chế độ chọn người chơi
          if (countCheck > 29) {
            countCheck = 0;
            Serial.println("--CHINH SL NGUOI CHOI");
            bool exitFlag = false;
            while (1) {

              if (!digitalRead(button1))
              {
                delay(DELAY_PUSH_BT);
                // Tang sl nguoi choi
                Serial.println("Tang sl nguoi choi");
              }
              if (!digitalRead(button3))
              {
                delay(DELAY_PUSH_BT);
                // Giam sl nguoi choi
                Serial.println("GIAM sl nguoi choi");
              }
              if (!digitalRead(button2))
              {
                delay(DELAY_PUSH_BT);
                countCheck = 0;
                while (!digitalRead(button2))
                {
                  countCheck++;
                  delay(DELAY_HOLD_BT);
                  if (countCheck > 20)
                  {
                    Serial.println("--Chot so luong nguoi choi la: ");
                    exitFlag = true;
                    break;
                  }
                }
              }
              if (exitFlag)
                break;
            }
          }
        }

        // Nút chức năng (start/chuyển mode)
        if (!digitalRead(button2))
        {
          delay(DELAY_PUSH_BT);
          countCheck = 0;
          while (!digitalRead(button2))
          {
            delay(DELAY_PUSH_BT);
            countCheck++;
            if (countCheck > 30)
              break;
          }
          if (countCheck < 20)
          {
            // Phát nhạc và chơi
            delay(2000);
            Serial.println("Truth Or Dare????");
            Randon_Affect();
            Serial.println("Wheel random");
            while (true)
            {
              if (!digitalRead(button1))
              {
                delay(DELAY_PUSH_BT);
                Serial.println("Truth");
                mplayer.play_random_mp3("truth_or_dare/dare/Track001.mp3", 6);
                break;
              }
              if (!digitalRead(button3))
              {
                delay(DELAY_PUSH_BT);
                Serial.println("Truth");
                mplayer.play_random_mp3("truth_or_dare/truth/Track001.mp3", 6);
                break;
              }
            }
          }
          else {
            Serial.println("Thoat tro choi truth or dare");
            break;
          }
        }
      }
#endif
      break;*/

    case WHO_FASTER_CLICK:
      Serial.println("WhoFasterClick");
#ifndef DEBUG
      //      fc_game.start();
      //      fc_game.play();
      //      fc_game.end();
      while (1) {

        if (!digitalRead(button2))
        {
          delay(DELAY_PUSH_BT);
          delay(2000);
          for (byte i = 3; i >= 0; i--)
          {
            print7seg(i, i);
            delay(1000);

            while (1)
            {
              delay(10);
              if (!digitalRead(button1))
              {
                delay(50);
                ++score1;
              }
              if (!digitalRead(button3))
              {
                delay(50);
                ++score2;
              }
              Serial.println(String(score1) + "-" + String(score2));
              print7seg(score1, score2);
              if (score1 <= WIN_POINT && score2 <= WIN_POINT)break;
            }
            // Hieu ung nguoi chien thang
          }

        }
        //for (int i = 0; i < 20; i++) {
        //  print7seg(i,i);
        //  delay(1000);
        //}
      }
#endif
      break;

    case WHO_FASTER_QUESTION:
      Serial.println("WhoFasterQuestion");
      fq_game.play(mplayer);
      break;
  }
}

void print7seg(byte score1, byte score2) {
  byte d1 = score1 / 10;
  byte d2 = score1 % 10;
  byte d3 = score2 / 10;
  byte d4 = score2 % 10;
  uint8_t numberToPrint[] = {numberBin[d1], numberBin[d2], numberBin[d3], numberBin[d4]};
  sr.setAll(numberToPrint);
}

void Randon_Affect() {
  byte n = random(6, 15);
  for (int vong = 0; vong < n; vong++)
  {
    for (int j = 0; j < 10; j++) {
      if (j == 8) {
        digitalWrite(LED9, LOW );
        delay(50);
        digitalWrite(LED9, HIGH );
        delay(50);
      }
      else if (j == 9) {
        digitalWrite(LED10, LOW );
        delay(50);
        digitalWrite(LED10, HIGH );
        delay(50);
      }
      else {
        pcf.digitalWrite(j, LOW );
        delay(50);
        pcf.digitalWrite(j, HIGH );
        delay(50);
      }
    }
  }
  pcf.digitalWrite(n % 11, LOW);
}
