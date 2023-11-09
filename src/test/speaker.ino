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

void setup() {
}

void loop(){
    int startMelody[] = { NOTE_C3, NOTE_D3, NOTE_E3, NOTE_C3, NOTE_G3, NOTE_B4, 0, NOTE_C4,0,0,0,0,0,0,0,0 };
     for(int i = 0;i<16;i++ ){
        playNote(startMelody[i],4);
        delay(500);
        }
}