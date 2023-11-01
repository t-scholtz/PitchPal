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

int SIG_PIN = 0;
int SPEAKER = 3;
int MUX_PIN0 = 8;
int MUX_PIN1 = 9;
int MUX_PIN2 = 10;
int MUX_PIN3 = 11;
int MICROPHONE  = 14;

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

  mic_setup();
  initializeLCD();
}

void loop() {
  double freq = getMicFrequency();
  printFreq(freq);
}

