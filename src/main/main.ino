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



