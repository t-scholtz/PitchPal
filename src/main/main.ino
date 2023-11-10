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
  State 0 - Will be start up animations
  State 1 - User Choses what state they want
*/
  switch (state)
  {
  case 1:
    state = stateSelector();
  case 2:
    break;
  case 3:
    state = findingNote();
  
  case 0:
  default:
    startUpAnim();
  }
}

//Temp Function to handle simple user input for now
int stateSelector(){
  int chosenState = 1;
  lcdClear();
  lcdPrint("1-Check Pitch\n2-Find Note 3-R")
  delay(1000)
  int button = waitForUserInput();
  if(button == 0) return 1;
  if(button == 1) return 2;
  if(button == 2) return 0;
  lcdClear();
  lcdPrint("Error detected in\ninput try again");
  return chosenState;
}

int findingNote(){
    

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


