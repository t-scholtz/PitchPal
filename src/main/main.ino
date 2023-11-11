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
  startUpAnim();
  Serial.println("LCD - Set");
  Serial.println("Initialized!!");
}

void loop() {
/* Main Loop for Project
  Works by Storing system state in  state(intialzed above)
  State 0 - Will be start up animations
  State 1 - Start the Pitch pal
  Buttons 0-11 are for notes and Octave
  Button 12 Back Button
  Button 13 Enter Button
  Button 14 - 15 WildCard
*/
  String goalNote = "!!!!!!";//Initilize our goals
  int goalOctave = 0;
  int goalNoteNum = 0;

  String currentNote = "!!!!!!";//Current ones uses to calculate
  int currentOctave = 0;
  int currentNoteNum = 0;

  tuple<String, float, NULL> N&O; //declaring the tuple we can use for notes and octaves

  int state = 1; //starting values
  int buttonInput = -1;

  int tempNUMSTATE; //this is used if an inappropriate button was hit

  switch (state)
  {
  case 1: //this will be the starting prompt
    starterState();
    buttonInput = confirmButton(buttonInput);
    if(buttonInput == 13){state = 2}

  case 2: //this is the Note gathering state
    goalNoteNum = pickingANote();
    if(goalNoteNum == -1){
      state = 1;
    }else if(goalNoteNum == -2){
      tempNUMSTATE = state;
      state = 0; //ERROR OCCURED
    }else{
      state = 3; //OCTAVE
    }

  case 3: //this is the OCTAVE gathering state
    goalOctave = pickingAOctave();
    if(goalNoteNum == -1){
      state = 2;
    }else if(goalNoteNum == -2){
      tempNUMSTATE = state;
      state = 0; //ERROR OCCURED
    }else{
      state = 3; //OCTAVE
    }

  
  case 0:
  default:
    lcdPrint("Error")
    Serial.println("Error")
    state = tempNUMSTATE;
  }


  "switch (state)
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
  }"
}

//Temp Function to handle simple user input for now
int stateSelector(){
  int chosenState = 1;
  lcdClear();
  //lcdPrint("1-Check Pitch\n2-Find Note 3-R")
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

int freqAnalyse(int note){ //we want this to idealy be 1 or a small variation, Think about having this handle multuliple and checking the most frequent one
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


