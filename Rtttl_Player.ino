#include <Arduino.h>

#define BUZZER_PIN 8

const float noteFrequencies[] = {
  30.87, 32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74,
  65.41, 69.30, 73.42, 77.78, 82.41, 87.31, 92.50, 98.00, 103.83, 110.00, 116.54, 123.47,
  130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94,
  261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88,
  523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00, 932.33, 987.77,
  1046.50, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 1760.00, 1864.66, 1975.53,
  2093.00, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520.00, 3729.31, 3951.07,
  4186.01, 4434.92, 4698.64, 4978.03
};

void playRTTTL(const char *song){
  int defaultDuration = 4;
  int defaultOctave = 5;
  int bpm = 102;
  int wholenote, duration;
  int note, scale;

  while (*song != ':') song++;
  song++;

  while (*song != ':'){
    if (*song == 'd'){
      song += 2;
      defaultDuration = atoi(song);
    }else if (*song == 'o'){
      song += 2;
      defaultOctave = atoi(song);
    }else if (*song == 'b'){
      song += 2;
      bpm = atoi(song);
    }
    while (*song != ',' && *song != ':') song++;
    if (*song == ':') break;
    song++;
  }
  song++;

  wholenote = (60 * 1000L / bpm) * 4;

  while (*song){
    int num = 0;

    while (*song >= '0' && *song <= '9'){
      num = (num * 10) + (*song - '0');
      song++;
    }

    duration = (num) ? wholenote / num : wholenote / defaultDuration;

    note = 0;
    switch (*song){
      case 'c': note = 1; break;
      case 'd': note = 3; break;
      case 'e': note = 5; break;
      case 'f': note = 6; break;
      case 'g': note = 8; break;
      case 'a': note = 10; break;
      case 'b': note = 12; break;
      case 'p': note = 0; break;
    }

    song++;

    if (*song == '#'){
      note++;
      song++;
    }

    if (*song >= '0' && *song <= '9'){
      scale = *song - '0';
      song++;
    }else{
      scale = defaultOctave;
    }

    scale -= 1;

    if (*song == '.'){
      duration += duration / 2;
      song++;
    }

    if (*song == ',') song++;

    if (note){
      tone(BUZZER_PIN, noteFrequencies[(scale * 12) + note], duration * 0.9);
    }

    delay(duration);
    noTone(BUZZER_PIN);
  }
}

//const char *song = "tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
//const char *song = "Arkanoid:d=4,o=5,b=140:8g6,16p,16g.6,2a#6,32p,8a6,8g6,8f6,8a6,2g6";
//const char *song = "mario:d=4,o=5,b=140:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";
const char *song = "TakeOnMe:d=8,o=5,b=170:f#,f#,f#,d,p,b4,p,e,p,e,p,e,g#,g#,a,b,a,a,a,e,p,d,p,f#,p,f#,p,f#,e,e,f#,e,f#,f#,f#,d,p,b4,p,e,p,e,p,e,g#,g#,a,b,a,a,a,e,p,d,p,f#,p,f#,p,f#,e,e5";

void setup() {
  playRTTTL(song);
}

void loop() {
}