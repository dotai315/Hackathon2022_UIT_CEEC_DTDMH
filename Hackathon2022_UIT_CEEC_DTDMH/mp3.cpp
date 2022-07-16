#include "mp3.h"
SdFat sd;
void mp3::begin()
{
  Serial.print(F("F_CPU = "));
  Serial.println(F_CPU);
  Serial.print(F("Free RAM = ")); // available in Version 1.0 F() bases the string to into Flash, to use less SRAM.
  Serial.print(FreeStack(), DEC);  // FreeStack() is provided by SdFat
  Serial.println(F(" Should be a base line of 1028, on ATmega328 when using INTx"));


  //Initialize the SdCard.
  if (!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
  // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
  if (!sd.chdir("/")) sd.errorHalt("sd.chdir");

  //Initialize the MP3 Player Shield
  int result = MP3player.begin();
  //check result, see readme for error codes.
  if (result != 0) {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to start MP3 player"));
    if ( result == 6 ) {
      Serial.println(F("Warning: patch file not found, skipping.")); // can be removed for space, if needed.
      Serial.println(F("Use the \"d\" command to verify SdCard can be read")); // can be removed for space, if needed.
    }
  }

#if defined(__BIOFEEDBACK_MEGA__) // or other reasons, of your choosing.
  // Typically not used by most shields, hence commented out.
  Serial.println(F("Applying ADMixer patch."));
  if (MP3player.ADMixerLoad("admxster.053") == 0) {
    Serial.println(F("Setting ADMixer Volume."));
    MP3player.ADMixerVol(-3);
  }
#endif

  if (!MP3player.isPlaying()) {
    // prevent root.ls when playing, something locks the dump. but keeps playing.
    // yes, I have tried another unique instance with same results.
    // something about SdFat and its 500byte cache.
    Serial.println(F("Files found (name date time size):"));
    sd.ls(LS_R | LS_DATE | LS_SIZE);
  } else {
    Serial.println(F("Busy Playing Files, try again later."));
  }
}

char *mp3::random_path_mp3(char* path, int _max_size)
{
  char* rand_path = path;
  char str [3] ;
  int len = strlen(rand_path);
  sprintf(str, "%03d", random(1, _max_size));
  rand_path[len - 7] = str[0];
  rand_path[len - 6] = str[1];
  rand_path[len - 5] = str[2];
  return rand_path;
}
void mp3::play_random_mp3(char* path, int max_size ) {
  char* trackFile = random_path_mp3(path, max_size);
  Serial.println(trackFile);

  int result = MP3player.playMP3(trackFile);
  //check result, see readme for error codes.
  if (result != 0) {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to play track"));
  }
}

void mp3::stop_track() {
  MP3player.stopTrack();
}
