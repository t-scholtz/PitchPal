#include <Arduino.h>
#include <WString.h>
#include <arduinoFFT.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
#include "input.h"  
#include "output.h"  
#include "pinlayout.h"
#include "pitches.h"
#define LOW 1000.0

String noteToString(int note){
  String ar[12]={
/*C*/     "C",
/*C#Db*/  "C#/Db",
/*D*/     "D",
/*D#Eb*/  "D#/Eb",
/*E*/     "E", 
/*F*/     "F", 
/*F#/Gb*/ "F#/Gb",
/*G*/     "G", 
/*G#/Ab*/ "G#/Ab",
/*A*/     "A",
/*A#Bb*/  "A#/Bb",
/*B*/     "B" 
  };
  return (ar[note]);
}

int noteArray(int a, int b) {
  int ar[12][5]={
/*C*/     {NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5},
/*C#Db*/  {NOTE_CS1, NOTE_CS2, NOTE_CS3, NOTE_CS4, NOTE_CS5},
/*D*/     {NOTE_D1, NOTE_D2, NOTE_D3, NOTE_D4, NOTE_D5},
/*D#Eb*/  {NOTE_DS1, NOTE_DS2, NOTE_DS3, NOTE_DS4, NOTE_DS5},
/*E*/     {NOTE_E1, NOTE_E2, NOTE_E3, NOTE_E4, NOTE_E5},
/*F*/     {NOTE_F1, NOTE_F2, NOTE_F3, NOTE_F4, NOTE_F5},
/*F#/Gb*/ {NOTE_FS1, NOTE_FS2, NOTE_FS3, NOTE_FS4, NOTE_FS5},
/*G*/     {NOTE_G1, NOTE_G2, NOTE_G3, NOTE_G4, NOTE_G5},
/*G#/Ab*/ {NOTE_GS1, NOTE_GS2, NOTE_GS3, NOTE_GS4, NOTE_GS5},
/*A*/     {NOTE_A1, NOTE_A2, NOTE_A3, NOTE_A4, NOTE_A5},
/*A#Bb*/  {NOTE_AS1, NOTE_AS2, NOTE_AS3, NOTE_AS4, NOTE_AS5},
/*B*/     {NOTE_B1, NOTE_B2, NOTE_B3, NOTE_B4, NOTE_B5}
  };
  if(a>12 || a<0){
    return -1;
  }
  if(b>7 || b<0){
    return -1;
  }
  return ar[a][b];
}


int muxChannel(int a, int b){
  int ar[16][4] = {{0,0,0,0}, //channel 0
  {1,0,0,0}, //channel 1
  {0,1,0,0}, //channel 2
  {1,1,0,0}, //channel 3
  {0,0,1,0}, //channel 4
  {1,0,1,0}, //channel 5
  {0,1,1,0}, //channel 6
  {1,1,1,0}, //channel 7
  {0,0,0,1}, //channel 8
  {1,0,0,1}, //channel 9
  {0,1,0,1}, //channel 10
  {1,1,0,1}, //channel 11
  {0,0,1,1}, //channel 12
  {1,0,1,1}, //channel 13
  {0,1,1,1}, //channel 14
  {1,1,1,1}  //channel 15
};
   if(a>16 || a<0){
    return " ";
  }
  if(b>4 || b<0){
    return " ";
  }
  return ar[a][b];

}



double getMicFrequency(){ 
  //Serial.println("mic freq started");
  Serial.println("mic freq started");
  arduinoFFT FFT = arduinoFFT();
  unsigned int samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));
  unsigned long microSeconds;
  double vReal[SAMPLES]; //creates vector/array of size SAMPLES to hold real values
  double vImag[SAMPLES]; // creates vector/array of size SAMPLES to hold imaginary values

  for(int i = 0; i<SAMPLES; i++){
    microSeconds = micros();   //Returns the amound of micro seconds sense the arduino boatd stated to run
    vReal[i] = analogRead(MICROPHONE);  //Reads the value from analog pin 14 (A0), quantize it and save it as a real term.
    vImag[i] = 0; //Makes imaginary term 0 always
    //remaining wait time between samples if necessary
    while(micros() < (microSeconds+samplingPeriod)){
      //do nothing----THiNK ABOUT LATER
    }
  }
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  return(peak);   
}

float getMuxInput(int channel){
  int controlPin[4] = {MUX_PIN0, MUX_PIN1, MUX_PIN2, MUX_PIN3};
  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel(channel,i)); //first par controls the area to change //second par controls the value(high, low) to change first to
  }
  int val = analogRead(SIG_PIN);
  float voltage = (val * 5.0) / 1024.0; 
  return voltage; //Does this voltage give us the number for the input to translate?
}

//Will return an number -1 to 15 with -1 meaning 2 or more buttons were detected being pressed at the same or when there was no button pressed
int checkForButtonPress(){
  int controlPin[] = {MUX_PIN0, MUX_PIN1, MUX_PIN2, MUX_PIN3};
  float buttons[16];
  //Read from every channel and grab the value at that point of time
  for(int i = 0; i<16 ; i++){
    for(int j = 0; j < 4; j ++){
      digitalWrite(controlPin[j], muxChannel(i,j)); //setting each set of pins line by line to read
      //delay(1000);
    }
    buttons[i] = analogRead(SIG_PIN);
  }
  //Serial.println("Done");
  //delay(1000);
  //Flag will count how many channels have high value - more than one indicates that 2 or more buttons pressed at same time which will return -1
  int flag = 0;
  int output = 0;
  for(int i = 0; i<16 ; i++){//runs 16 times, stops at 16
    if (buttons[i] > LOW ){
      flag++;
      output = i;
    }
  }
  if (flag == 1){
    return output;
    }
  else if(flag > 1){
    return -1;
  }
  return -1;//return the button number
}

//Will wait for user input, and return 0-15 for valid iput, and -1 for invalid
int waitForUserInput(){ //ASK tim if this one is needed, we have checkButtonPress and another making sure the button press is correct
  int controlPin[] = {MUX_PIN0, MUX_PIN1, MUX_PIN2, MUX_PIN3};
  float buttons[16];
  //condition varible waiting for usr input to be detected
  bool stillWating = true;
  while(stillWating){
    //Read from every channel and grab the value at that point of time
    for(int i = 0; i<16 ; i++){
      for(int j = 0; j < 4; j ++){
        digitalWrite(controlPin[j], muxChannel(i,j)); //setting each set of pins line by line to read
      }
      buttons[i] = analogRead(SIG_PIN);//setting each button signifier to a value of high or low
      if( buttons[i] > LOW) stillWating = false;
    }
  }
  //Flag will count how many channels have high value - more than one indicates that 2 or more buttons pressed at same time which will return -1
  int flag = 0;
  int output = -1;
  for(int i = 0; i<16 ; i++){//runs 16 times, stops at 16
    if (buttons[i] > LOW ){
      flag++;
      output = i;
    }
  }
  if (flag != 1){
    return -1;}
  return output;//return the button number
}


//Will wait for user input will scrolling through text
int waitScrollingText(){

  //Initialize 
  int controlPin[] = {MUX_PIN0, MUX_PIN1, MUX_PIN2, MUX_PIN3};
  float buttons[16];

  //condition varible waiting for usr input to be detected
  bool stillWaiting = true;
  String wait = "waiting for ";
  String input="   input";
  int messageCount = 0;
  lcdPrint("1 - pitch practice ",wait);
  delay(TEXT_DELAY);

  while(stillWaiting){
    messageCount += 1;
    if(messageCount == 150){
      
     lcdPrint("2 - play listen notet",input);
    }
    else if(messageCount ==300){
       lcdPrint("3 - find note ",wait);
    }
     else if(messageCount == 450){
       lcdPrint("15 - reset",input);
    }
     else if(messageCount >600){
       lcdPrint("1 - pitch practice ",wait);
       messageCount =0;
    }

    //Read from every channel and grab the value at that point of time
    for(int i = 0; i<16 ; i++){
      for(int j = 0; j < 4; j ++){  
        digitalWrite(controlPin[j], muxChannel(i,j)); //setting each set of pins line by line to read
      }
      buttons[i] = analogRead(SIG_PIN);//setting each button signifier to a value of high or low
      if( buttons[i] > LOW){ stillWaiting = false;
    }
  }
  }
  
//Flag will count how many channels have high value - more than one indicates that 2 or more buttons pressed at same time which will return -1
  int flag = 0;
  int output = -1;
  for(int i = 0; i<16 ; i++){//runs 16 times, stops at 16
    if (buttons[i] > LOW ){
      flag++;
      output = i;
    }
  }
  if (flag != 1){
    return -1;}
  return output;//return the button number
}


//Selects note Values
//Retunr -1 if person want to canclle
//Returns 0 - 11 if a correct not was chosen
//Reutns Repeats if detects invalid input
int selectNote(){
  while(true){
    lcdPrint("Select Note ", "Options 1-12");
    delay(TEXT_DELAY);
    int goalNoteNum = waitForUserInput();

    if (goalNoteNum == 15){ //RESET
      lcdPrint("Reseting Device","Stand By");
      delay(TEXT_DELAY);
      return -1;
    }
    else if (goalNoteNum != -1 && goalNoteNum<12 ){
      lcdPrint("Selected :"+noteToString(goalNoteNum) , "Confirm :14");
      delay(TEXT_DELAY);
      int confirm = waitForUserInput();
      if(confirm == 14){
        return goalNoteNum;
      }
    }
    else{
      lcdPrint("input Error","Try again");
      delay(TEXT_DELAY);
    }
  }
  return 1;
}

int selectOctave(){
  while(true){
    lcdPrint("Select Octave ", "Options 1-8");
    delay(TEXT_DELAY);
    int goalOctNum = waitForUserInput();

    if (goalOctNum == 15){ // Goes back
      lcdPrint("Reseting Device","Stand By");
      delay(TEXT_DELAY);
      return -1;
    }
    else if (goalOctNum != -1 && goalOctNum<8 ){
      lcdPrint("Selected :" + String(goalOctNum) , "Confirm :14");
      delay(TEXT_DELAY);
      int confirm = waitForUserInput();
      if(confirm == 14){
        return goalOctNum;
      }
    }
    else{
      lcdPrint("Input Error Detected","Try again");
      delay(TEXT_DELAY);
    }
  }
  return 1;
}

//EDGE CASE - if value is inbetween 2 rows
//Tries to find the closest match to given frequency, with a perentage of confindence
String noteFinder(double freqOfNote){
  int noteIndex =11;
  int octIndex = 6;
  bool found = false;

  //check if note is inside of possible range, may want to make edge cases more inclusive though
  if (freqOfNote > noteArray(noteIndex,octIndex)) return "Too High";
  if (freqOfNote < noteArray(0,0)) return "Too Low";

  //Loop from the highest octave of C to the lowest octave of C, to find which octave the note is in
  //octIndex starts at 6, 
  //(check if current freq is greater than C7 with range of error AND make sure we dont go to an incorrect index) checks if still true
  //octIndex -= 1, will the lowest index be 1 or 0 in C++??
  for(octIndex=6; freqOfNote < noteArray(0,octIndex)*0.98 && octIndex>-1; octIndex--);
  
  //loop from C to B and find between wich notes output exists
  //starts from C, the first note in a octave
  //will make sure freqNote never dips under the 
  for(noteIndex=0; freqOfNote > noteArray(noteIndex,octIndex) && noteIndex<13; noteIndex++); //it is 13 SO if it becomes 12 we know it's the edge case between octaves
  
  //Find which one is closer and returns note + confidnece score
  if(noteIndex==12){
    if(abs(1-freqOfNote/noteArray(noteIndex-1,octIndex))>abs(1-freqOfNote/noteArray(0,octIndex+1))){
      return  noteToString(noteIndex-1) + " " +int(freqOfNote/noteArray(noteIndex-1,octIndex)) + "%";//Need to look how this gets printed out with an integer
    }
    else{
      return  noteToString(0) + " " +int(noteArray(0,octIndex+1)/freqOfNote) + "%";
    }
  }//This is checking our edge case
  else{
    if(abs(1-freqOfNote/noteArray(noteIndex-1,octIndex))>abs(1-freqOfNote/noteArray(noteIndex,octIndex))){
      return noteToString(noteIndex-1) + " " +int(freqOfNote/noteArray(noteIndex-1,octIndex)) + "%";//Need to look how this gets printed out with an integer
    }
    else{
      return  noteToString(0) + " " +int(noteArray(noteIndex,octIndex)/freqOfNote) + "%";
    }
  }//This checks normally 
  
}






