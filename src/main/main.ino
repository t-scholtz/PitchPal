/*********************************************/
/* Name of the program: */
/* Author: Timothy Scholtz ; Thomoas Mahok */
/* C program file name: */
/* Date: 10/6/2023 */
/*********************************************/

#include <Arduino.h>
#include <WString.h>
#include "pinlayout.h"
#include "input.h"
#include "output.h"
#include "pitches.h"

void setup()
{
  Serial.begin(SERIAL_RATE);

  pinMode(MUX_PIN0, OUTPUT);
  pinMode(MUX_PIN1, OUTPUT);
  pinMode(MUX_PIN2, OUTPUT);
  pinMode(MUX_PIN3, OUTPUT);

  digitalWrite(MUX_PIN0, LOW);
  digitalWrite(MUX_PIN1, LOW);
  digitalWrite(MUX_PIN2, LOW);
  digitalWrite(MUX_PIN3, LOW);

  micSetup();
  initializeLCD();
  //startUpAnim();
}

int noteSelect = 0;
int octaveSelect =0;

/* Main Loop for Project
    State machine
    case 1: Main Menu
    case 2: Pitch Practice
    csee 3: Play Note
    case 4: Indentify Pitch
    Defualt - Go to state 1
  */
int state = 1; // starting values
void loop()
{
  switch (state)
  {
  case 1: // Menu Page
    reset();
    state = stateSelector();
    break;
  case 2: //User choses note and gets feedback
    state = pitchPractice();
    break;
  case 3: //User chooses a note and speaker plays it
    state = notePlaying();
    break;
  case 4: //Listens to user audio and determines 
          //what note is being played
    state = pitchFind();
    break;
  default:
    state = 1;
    break;
  }
}
//resets user prefrances
void reset(){
  noteSelect = 0;
  octaveSelect =0;
}

// Prints menu of options and wait for user input
int stateSelector()
{
  //Rolling text of options, whilst waiting for user to press a button. Can change string as nessary if we update options, just update switch below to match
  int button = waitScrollingText();
  if (button == 0)
  {
    return 2; // Pitch Practice
  }
  if (button == 1)
  {
    return 3; //Play note auiod 
  }
  if (button == 2)
  {
    return 4; // Detect note being played
  }
  if( button == 3){

    return 6;
  }
  if( button == 15){
    return 0;
  }
  lcdClear();
  lcdPrint("Error detected in","input try again");
  return 1;
}

//Core function of Project
//Select note, listen to note give feed back
//TO DO - implement fancy outputs
int pitchPractice(){
  lcdClear();
  lcdPrint("Pitch","Practice");
  delay(TEXT_DELAY);
  //Select Note, and if cancle chosen, do accordingly
  noteSelect = selectNote();
  //Serial.println("Note: " + String(noteSelect));
  if(noteSelect == -1){
    return 1;
  }
  //Select Octave, and if cancle chosen, do accordingly
  octaveSelect = selectOctave();
  //Serial.println("Ocatave: " + String(octaveSelect));
  if(octaveSelect == -1){
    return 1;
  }

  lcdPrint("Listening", "");
  delay(TEXT_DELAY);
  //Give feed back on performance
  double freq = getMicFrequency();
  
  lcdPrint("Made it past", "");
  delay(TEXT_DELAY);

  int goal = noteArray(noteSelect,octaveSelect);
  while(freq){
    //Serial.println(freq);
  //close is a ratio between actural note and desired note
  //if I wanted 440hz, but got 220, close would be 50%, and conversly if I got 880, input would be 150%
  //This somewhat takes into considerations differences in higher and lower pitchs, eg
  //if Execetd is 40, but actual 60, close is %150 which is really off due to a diff of 20Hz
  //if Execetd is 440, but actual 460, close is %104 which is really close due to a diff of 20Hz
    double close = freq/goal;
    //These values will need to be adapted
    if(close<0.95){
      lcdPrint("Too flat","Any button exit");
    }
    else if(close>1.08){
      lcdPrint("Too Sharp","Any button exit");
    }
    else{
      lcdPrint("Sounds Good","Any button exit");
    }
    if(checkForButtonPress()!=-1){
      return 1;
    }
  }
  return 1;
}

//user selects note and audio is plated
int notePlaying(){
  lcdPrint("Play Note","");
  delay(TEXT_DELAY);
  //Select Note, and if cancle chosen, do accordingly
  noteSelect = selectNote();
  if(noteSelect == -1){
    lcdPrint("NOTE E","");
    delay(TEXT_DELAY);
    return 1;
  }
  //Select Octave, and if cancle chosen, do accordingly
  octaveSelect = selectOctave();
  lcdPrint("OCTAVE PASS","");
  delay(TEXT_DELAY);

  if(octaveSelect == -1){
    lcdPrint("OCTAVE E","");
    delay(TEXT_DELAY);
    return 1;
  }
  int button = -1;
  while(button != 1){
    lcdPrint("WHILE LOOP","");
    delay(TEXT_DELAY);

    String TestNote = noteStrArray(noteSelect,octaveSelect);
    lcdPrint(TestNote,"TESTING NOTE");
    delay(TEXT_DELAY);

    lcdPrint("Playing: "+noteStrArray(noteSelect,octaveSelect), "Press 1 to exit");
    delay(TEXT_DELAY);
    playNote(noteArray(noteSelect,octaveSelect), 2);
    button = waitForUserInput();
  }
  return 1;
}

//trys to determine what note is being played
int pitchFind(){
  double freq;
  while(true){
    freq = getMicFrequency();
    lcdPrint("Note: "+noteFinder(freq) ,"Any button exit");
    if(checkForButtonPress() !=-1){
      return 1;
    }
  }
}







