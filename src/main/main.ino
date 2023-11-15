// #include <MicroTuple.h>

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
// #include <tuple>

void setup()
{
  Serial.begin(SERIAL_RATE);
  Serial.println("Initializing PitchPal"); // Testing

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

void loop()
{
  /* Main Loop for Project
    Works by Storing system state in  state(intialzed above)
    State 0 - Will be start up animations
    State 1 - Start the Pitch pal
    Buttons 0-11 are for notes and Octave
    Button 12 Back Button
    Button 13 Enter Button
    Button 14 - 15 WildCard
  */
  String goalNote = "!!!!!!"; // Initilize our goals
  int goalOctave = 0;
  int goalNoteNum = 0;
  double goalNoteFREQ = 0;

  String currentNote = "!!!!!!"; // Current ones uses to calculate
  // int currentOctave = 0;
  // int currentNoteNum = 0;
  double currentNoteFREQ = 0;

  int state = 1; // starting values
  int buttonInput;
  int enterCheck;

  int tempNUMSTATE; // this is used if an inappropriate button was hit

  long timer; //what we are gonna use for the millaseconds

  switch (state)
  {
  case 1: // this will be the starting prompt
    starterState();
    buttonInput = confirmButton(buttonInput);
    if (buttonInput == 13){
      state = 2;
    }

  case 2: // this is the Note gathering state
    goalNoteNum = pickingANote();
    if (goalNoteNum == -1){ // Goes back
      state = 1;
    }
    else if (goalNoteNum == -2){
      tempNUMSTATE = state;
      state = 0; // ERROR OCCURED
    }
    else{
      state = 3; // OCTAVE
    }

  case 3: // this is the OCTAVE gathering state
    goalOctave = pickingAOctave();
    if (goalNoteNum == -1){ // Goes back
      state = 2;
    }
    else if (goalNoteNum == -2){
      tempNUMSTATE = state;
      state = 0; // ERROR OCCURED
    }
    else{
      state = 4; // OCTAVE
    }

  case 4: // this is the confirming stage //This is the start of Stage 2
    // N&O = stageOneNote(goalNoteNum, goalOctave);
    goalNote = noteStrArray(goalNoteNum, goalOctave);
    goalNoteFREQ = noteArray(goalNoteNum, goalOctave);
    lcdClear();
    stageTwoPrompt(goalNote);
    enterCheck = confirmButton(-1);
    if (enterCheck == 13){
      state = 5; // going forwards
    }
    else if (enterCheck = 12){
      state = 3; // going backwards
    }
    else{
      tempNUMSTATE = state;
      state = 0; // ERROR OCCURED
    }

  case 5: // Playing the sound of the Note
    noteExamplePrompt();
    playNote(goalNoteFREQ, 10);
    buttonInput = confirmButton(-1);
    if (buttonInput == 13){
      state = 6; // going forwards
    }
    else if (buttonInput = 12){
      state = 4; // going backwards
    }

  case 6: // Here is the big listening  //We have an issue that we need to look at with either the sample size or mabye just the arduino board. For voices it will be fine but I noticed that most correct tones are about .02 max .03 off until you get to the really high tones.
    listeningPrompt();
    //have it listen for 10 seconds and show option to be done for 1 check of 5 seconds
    timer = millis(); //we will change after 10 seconds from this point
    while((timer+15000) > millis()){//this should make it run for 
      updatingPrompt( goalNote,noteFinder(currentNoteFREQ));
      if(currentNote == goalNote){
        //Make LED's do something crazy
        lcdClear();
        lcdPrint("YOU DID IT\n!!Keep practing!!");
        delay(3000);
      }
    } 
    timer = millis();
    while((timer+5000) > millis()){
      finisherPrompt();
      buttonInput = confirmButton(-1);
      if (buttonInput == 13){
        state = 1; //ending
        break;
      }
      else if(buttonInput > -1){
        tempNUMSTATE = state;
      state = 0; // ERROR OCCURED
      }
    }
  default:
    invalidPrompt();
    Serial.println("Error");
    state = tempNUMSTATE;
  }
}

// Temp Function to handle simple user input for now
int stateSelector()
{
  int chosenState = 1;
  lcdClear();
  // lcdPrint("1-Check Pitch\n2-Find Note 3-R")
  delay(1000);
  int button = waitForUserInput();
  if (button == 0)
  {
    return 1;
  }
  if (button == 1)
  {
    return 2;
  }
  if (button == 2)
  {
    return 0;
  }
  lcdClear();
  lcdPrint("Error detected in\ninput try again");
  return chosenState;
}

int findingNote()
{
}

// int freqAnalyse(int note){ //we want this to idealy be 1 or a small variation, Think about having this handle multuliple and checking the most frequent one
//   //loop condition
//   int input = -1;
//   while(input <0){
//     //Get mic freq
//     double realFreq = double getMicFrequency();
//     double errorPerc = (note - realFreq)/realFreq;
//     String errorPercStr = to_string(errorPerc);
//     //Compare real to desired noe
//     lcdPrint(errorPercStr);
//     //Look for user input to cancle
//     input = checkForButtonPress();
//   }
//   return input;
// }
