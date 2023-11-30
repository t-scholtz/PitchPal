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
  startUpAnim();
}

int noteSelect = 0;
int octaveSelect =1;

void loop()
{
  /* Main Loop for Project
    State machine
    case 1: Main Menu
    case 2: Pitch Practice
    csee 3: Play Note
    case 4: Indentify Pitch
    Defualt - Go to state 1
  */
  int state = 1; // starting values
  switch (state)
  {
  case 1: // this will be the starting prompt
    reset();
    state = stateSelector();
  case 2:
    state = pitchPractice();
  case 3: // Playing the sound of the Note
    state = notePlaying();
  case 4:
    state = pitchFind();
  // case 6: // Here is the big listening  //We have an issue that we need to look at with either the sample size or mabye just the arduino board. For voices it will be fine but I noticed that most correct tones are about .02 max .03 off until you get to the really high tones.
  //   listeningPrompt();
  //   //have it listen for 10 seconds and show option to be done for 1 check of 5 seconds
  //   timer = millis(); //we will change after 10 seconds from this point
  //   while((timer+15000) > millis()){//this should make it run for 
  //     updatingPrompt( goalNote,  noteFinder(currentNoteFREQ));
  //     if(currentNote == goalNote){
  //       //Make LED's do something crazy
  //       lcdClear();
  //       lcdPrint("YOU DID IT\n!!Keep practing!!");
  //       delay(3000);
  //     }
  //   } 
  //   timer = millis();
  //   while((timer+5000) > millis()){
  //     finisherPrompt();
  //     enterCheck = confirmButton(-1);
  //     if (enterCheck == 13){
  //       state = 1; //ending
  //       break;
  //     }
  //     else if(enterCheck > -1){
  //       tempNUMSTATE = state;
  //     state = 0; // ERROR OCCURED
  //     }
  //   }
  default:
    state = 1;
  }

}


void reset(){
  noteSelect = 0;
  octaveSelect =1;
}

int pitchFind(){

}

int notePlaying(){
  lcdPrint("Play the","Note");
  delay(TEXT_DELAY);
  //Select Note, and if cancle chosen, do accordingly
  noteSelect = selectNote();
  if(noteSelect == -1){
    return 1;
  }
  //Select Octave, and if cancle chosen, do accordingly
  octaveSelect = selectOctave();
  if(octaveSelect == -1){
    return 1;
  }
  lcdPrint("Playing: "+noteStrArray(noteSelect,octaveSelect), "Press any to exit");
  int button = -1;
  int count = 0;
  //For exery 3 cycles, spends 3 playing audio, and one checking for user input
  while(button == -1){
    if(count>0) playNote(noteArray(noteSelect,octaveSelect), 500);
    if(count > 4){ 
      count = -4;
      button = checkForButtonPress();
      }
    count++;
  }
  return 1;
}

int pitchPractice(){
  lcdPrint("Pitch","Practice");
  delay(TEXT_DELAY);
  //Select Note, and if cancle chosen, do accordingly
  noteSelect = selectNote();
  if(noteSelect == -1){
    return 1;
  }
  //Select Octave, and if cancle chosen, do accordingly
  octaveSelect = selectOctave();
  if(octaveSelect == -1){
    return 1;
  }
  //Give feed back on performance
  double freq = getMicFrequency();
  int goal = noteArray(noteSelect,octaveSelect);
  double close = freq/goal;
  double diff = abs(1-close);
  //These values will need to be adapted
  if(close<0.95){
    lcdPrint("Too flat","Any button exit");
  }
  else if(close>1.10){
    lcdPrint("Too Sharp","Any button exit");
  }
  else{
    lcdPrint("Sounds Good","Any button exit");
  }
  if(checkForButtonPress()!=-1){
    return 1;
  }
  return 1;
}

// Temp Function to handle simple user input for now
int stateSelector()
{
  int chosenState = 1;
  delay(TEXT_DELAY);//?? why is there a delay here?
  int button = waitScrollingText("2 - pitch practice   3 - find note   4 - play listen note   5 - reset");//2 pitch practice, 3 play note for example, pitch find
  if (button == 0)
  {
    return 2;
  }
  if (button == 1)
  {
    return 3;
  }
  if (button == 2)
  {
    return 4;
  }
  if( button == 3){

    return 6;
  }
  if( button == 15){
    return 0;
  }
  lcdClear();
  lcdPrint("Error detected in","input try again");
  return chosenState;
}

int findingNote()
{
}

