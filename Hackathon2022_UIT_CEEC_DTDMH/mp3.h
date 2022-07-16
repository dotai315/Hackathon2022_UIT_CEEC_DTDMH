#pragma once
#include "Arduino.h"
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

class mp3
{
private:
  
  vs1053 MP3player; 
public:
  mp3() {}
  ~mp3() {}
  void begin();
  char *random_path_mp3(char* path, int _max_size);
  void play_random_mp3(char* path, int max_size );
  void stop_track();
};
