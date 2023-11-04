/*********************************************/
/* Name of the program: */
/* Author: Timothy Scholtz ; Thomoas Mahok */
/* C program file name: */
/* Date: 10/6/2023 */
/*********************************************/

#include <Arduino.h>
#include "pinlayout.h" 
#include "input.h" 
#include "output.h" 
#include "pitches.h"

int noteArray[][] = {
/*A*/     {NOTE_A1, NOTE_A2, NOTE_A3, NOTE_A4, NOTE_A5, NOTE_A6, NOTE_A7},
/*A#Bb*/  {NOTE_AS1, NOTE_AS2, NOTE_AS3, NOTE_AS4, NOTE_AS5, NOTE_AS6, NOTE_AS7},
/*B*/     {NOTE_B1, NOTE_B2, NOTE_B3, NOTE_B4, NOTE_B5, NOTE_B6, NOTE_B7},
/*C*/     {NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6, NOTE_C7},
/*C#Db*/  {NOTE_CS1, NOTE_CS2, NOTE_CS3, NOTE_CS4, NOTE_CS5, NOTE_CS6, NOTE_CS7},
/*D*/     {NOTE_D1, NOTE_D2, NOTE_D3, NOTE_D4, NOTE_D5, NOTE_D6, NOTE_D7},
/*D#Eb*/  {NOTE_DS1, NOTE_DS2, NOTE_DS3, NOTE_DS4, NOTE_DS5, NOTE_DS6, NOTE_DS7},
/*E*/     {NOTE_E1, NOTE_E2, NOTE_E3, NOTE_E4, NOTE_E5, NOTE_E6, NOTE_E7},
/*F*/     {NOTE_F1, NOTE_F2, NOTE_F3, NOTE_F4, NOTE_F5, NOTE_F6, NOTE_F7},
/*F#/Gb*/ {NOTE_FS1, NOTE_FS2, NOTE_FS3, NOTE_FS4, NOTE_FS5, NOTE_FS6, NOTE_FS7},
/*G*/     {NOTE_G1, NOTE_G2, NOTE_G3, NOTE_G4, NOTE_G5, NOTE_G6, NOTE_G7},
/*G#/Ab*/ {NOTE_GS1, NOTE_GS2, NOTE_GS3, NOTE_GS4, NOTE_GS5, NOTE_GS6, NOTE_GS7},
}

String noteStrArray[][] = {
/*A*/     {"A1", "A2", "A3", "A4", "A5", "A6", "A7"},
/*A#Bb*/  {"AS1", "AS2", "AS3", "AS4","AS5", "AS6", "AS7"},
/*B*/     {"B1", "B2", "B3", "B4", "B5", "B6", "B7"},
/*C*/     {"C1", "C2", "C3", "C4", "C5", "C6", "C7"},
/*C#Db*/  {"CS1", "CS2", "CS3", "CS4", "CS5", "CS6", "CS7"},
/*D*/     {"D1", "D2", "D3", "D4", "D5", "D6", "D7"},
/*D#Eb*/  {"DS1", "DS2", "DS3", "DS4", "DS5", "DS6", "DS7"},
/*E*/     {"E1", "E2", "E3", "E4", "E5", "E6", "E7"},
/*F*/     {"F1", "F2", "F3", "F4", "F5", "F6", "F7"},
/*F#/Gb*/ {"FS1", "FS2", "FS3", "FS4", "FS5", "FS6", "FS7"},
/*G*/     {"G1", "G2", "G3", "G4", "G5", "G6", "G7"},
/*G#/Ab*/ {"GS1", "GS2", "GS3", "GS4", "GS5", "GS6", "GS7"},
}


void setup() {
  Serial.begin(SERIAL_RATE);
  Serial.println("Initializing PitchPal");//Testing 

  pinMode(MUX_PIN0, OUTPUT);
  pinMode(MUX_PIN1, OUTPUT);
  pinMode(MUX_PIN2, OUTPUT);
  pinMode(MUX_PIN3, OUTPUT);

  digitalWrite(MUX_PIN0, LOW);
  digitalWrite(MUX_PIN1, LOW);
  digitalWrite(MUX_PIN2, LOW);
  digitalWrite(MUX_PIN3, LOW);
  Serial.println("Pin layout - Set!");

  micSetup();
  Serial.println("Mic - Set");
  initializeLCD();
  Serial.println("LCD - Set");
  Serial.println("Initialized!!");
  startUpAnim(); //Once this animation playes we set it up correctly 
}

// For now loop just runs through the basic I/O eg:
// plays a sound
// print to lcd screen
// grabss button input
// get freq from speaker
void loop() {
  delay(2000);
  // Serial.println("Loop Start");
  // playNote(NOTE_C4,4);
  // delay(2000);
  // playNote(NOTE_G3,4);
  double freq = getMicFrequency();
  printFreq(freq);
  delay(2000);
  // int buttonPressed =  checkForButtonPress();
  // String text = String(buttonPressed);
  // lcdPrint(text);
  // delay(2000);
}

//making the main loop we will need
void loop(){
  //stage One, choosing the Note

}

