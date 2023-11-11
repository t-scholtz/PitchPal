#include <Arduino.h>
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_B4 494
#define SPEAKER 3
#define NOTE_LENGTH 1000

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");
}

void loop(){
    int startMelody[] = { NOTE_CS3, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_F3, NOTE_GS3, NOTE_AS3, NOTE_FS3, NOTE_GS3, NOTE_GS3 };
     for(int i = 0;i<14;i++ ){
        playNote(startMelody[i],6);
        //delay(500);
        }
}

void playNote(int note, int length){ //this one should be relitivly simple 
    int noteDuration = NOTE_LENGTH / length;
    tone(SPEAKER, note, noteDuration);
    delay(noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(SPEAKER);
}