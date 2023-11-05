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
}

int state = 0;
void loop() {
/* Main Loop for Project
  Works by Storing system state in  state(intialzed above)
  State 0 - will be start up animations
  State 1 - Lets user select frequency
  State 2 - Reocrds and prints Freq value
*/
  switch (state)
  {
  case 1:
    break;

  case 2:
    break;
  
  case 0:
  default:
    startUpAnim();
  }

  delay(2000);
  Serial.println("Loop Start");
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


int freqAnalyse(int note){
  //loop condition
  int input = -1;
  while(input <0){
    //Get mic freq
    double realFreq = double getMicFrequency();
    double errorPerc = (note - realFreq)/realFreq;
    //Compare real to desired noe
    lcdPrint(errorPerc);
    //Look for user input to cancle
    input = checkForButtonPress();
  }
  return input;
}


