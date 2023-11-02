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
  pinMode(MUX_PIN0, OUTPUT);
  pinMode(MUX_PIN1, OUTPUT);
  pinMode(MUX_PIN2, OUTPUT);
  pinMode(MUX_PIN3, OUTPUT);

  digitalWrite(MUX_PIN0, LOW);
  digitalWrite(MUX_PIN1, LOW);
  digitalWrite(MUX_PIN2, LOW);
  digitalWrite(MUX_PIN3, LOW);

  Serial.begin(SERIAL_RATE);

  micSetup();
  initializeLCD();
}

void loop() {
  playNote(NOTE_C4,4);
  delay(2000);
  playNote(NOTE_G3,4);
  double freq = getMicFrequency();
  printFreq(freq);
  delay(2000);
  int buttonPressed =  checkForButtonPress();
  String text = String(buttonPressed);
  lcdPrint(text);
  delay(2000);
}

