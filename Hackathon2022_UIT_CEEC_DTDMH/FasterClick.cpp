#include "FasterClick.h"

FasterClick::FasterClick()
{
    this->countP1 = 0;
    this->countP2 = 0;
}

void FasterClick::begin(int button1, int button2)
{
    this->button1 = button1;
    this->button2 = button2;
}

void FasterClick::start()
{
  Serial.println("Start!!!");
  pinMode(this->button1, INPUT);
  pinMode(this->button2, INPUT);
}

void FasterClick::play()
{
  while(this->countP1 != 99 && this->countP2 != 99)
  {
    Serial.print("P1: ");
    Serial.println(this->countP1);
    Serial.print("P2: ");
    Serial.println(this->countP2);
    if (!digitalRead(this->button1))
    {
      while(!digitalRead(this->button1));
      this->countP1++;
    }
    if (!digitalRead(this->button2))
    {
      while(!digitalRead(this->button2));
      this->countP2++;
    }
  }
  Serial.print("P1: ");
  Serial.println(this->countP1);
  Serial.print("P2: ");
  Serial.println(this->countP2);
  if (this->countP1 == 99)
  {
    Serial.println("P1 Win");
  }
  if (this->countP2 == 99)
  {
    Serial.println("P2 Win");
  }
  delay(3000);
}

void FasterClick::end()
{
  this->countP1 = 0;
  this->countP2 = 0;
  this->button1 = -1;
  this->button2 = -1;
}
