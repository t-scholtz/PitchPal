#include <Arduino.h>
#include <WString.h>
#include <arduinoFFT.h>
#include <LiquidCrystal_I2C.h>


//#include <tuple>
#include "input.h"  
#include "output.h"  
#include "pinlayout.h"
#include "pitches.h"

#define LOW 1.0

arduinoFFT FFT = arduinoFFT();
unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES]; //creates vector/array of size SAMPLES to hold real values
double vImag[SAMPLES]; // creates vector/array of size SAMPLES to hold imaginary values

int noteArray(int a, int b) {
  int ar[12][7]={
/*C*/     {NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6, NOTE_C7},
/*C#Db*/  {NOTE_CS1, NOTE_CS2, NOTE_CS3, NOTE_CS4, NOTE_CS5, NOTE_CS6, NOTE_CS7},
/*D*/     {NOTE_D1, NOTE_D2, NOTE_D3, NOTE_D4, NOTE_D5, NOTE_D6, NOTE_D7},
/*D#Eb*/  {NOTE_DS1, NOTE_DS2, NOTE_DS3, NOTE_DS4, NOTE_DS5, NOTE_DS6, NOTE_DS7},
/*E*/     {NOTE_E1, NOTE_E2, NOTE_E3, NOTE_E4, NOTE_E5, NOTE_E6, NOTE_E7},
/*F*/     {NOTE_F1, NOTE_F2, NOTE_F3, NOTE_F4, NOTE_F5, NOTE_F6, NOTE_F7},
/*F#/Gb*/ {NOTE_FS1, NOTE_FS2, NOTE_FS3, NOTE_FS4, NOTE_FS5, NOTE_FS6, NOTE_FS7},
/*G*/     {NOTE_G1, NOTE_G2, NOTE_G3, NOTE_G4, NOTE_G5, NOTE_G6, NOTE_G7},
/*G#/Ab*/ {NOTE_GS1, NOTE_GS2, NOTE_GS3, NOTE_GS4, NOTE_GS5, NOTE_GS6, NOTE_GS7},
/*A*/     {NOTE_A1, NOTE_A2, NOTE_A3, NOTE_A4, NOTE_A5, NOTE_A6, NOTE_A7},
/*A#Bb*/  {NOTE_AS1, NOTE_AS2, NOTE_AS3, NOTE_AS4, NOTE_AS5, NOTE_AS6, NOTE_AS7},
/*B*/     {NOTE_B1, NOTE_B2, NOTE_B3, NOTE_B4, NOTE_B5, NOTE_B6, NOTE_B7}
  };
  if(a>12 || a<0){
    return -1;
  }
  if(b>7 || b<0){
    return -1;
  }
  return ar[a][b];
}

String noteStrArray(int a, int b) { 
  String ar[12][7] = {//putting them here temporarly so that we can function calling them //I want 
/*C*/     {"C1", "C2", "C3", "C4", "C5", "C6", "C7"},
/*C#Db*/  {"CS1", "CS2", "CS3", "CS4", "CS5", "CS6", "CS7"},
/*D*/     {"D1", "D2", "D3", "D4", "D5", "D6", "D7"},
/*D#Eb*/  {"DS1", "DS2", "DS3", "DS4", "DS5", "DS6", "DS7"},
/*E*/     {"E1", "E2", "E3", "E4", "E5", "E6", "E7"},
/*F*/     {"F1", "F2", "F3", "F4", "F5", "F6", "F7"},
/*F#/Gb*/ {"FS1", "FS2", "FS3", "FS4", "FS5", "FS6", "FS7"},
/*G*/     {"G1", "G2", "G3", "G4", "G5", "G6", "G7"},
/*G#/Ab*/ {"GS1", "GS2", "GS3", "GS4", "GS5", "GS6", "GS7"},
/*A*/     {"A1", "A2", "A3", "A4", "A5", "A6", "A7"},
/*A#Bb*/  {"AS1", "AS2", "AS3", "AS4","AS5", "AS6", "AS7"},
/*B*/     {"B1", "B2", "B3", "B4", "B5", "B6", "B7"}
  };
   if(a>12 || a<0){
    return " ";
  }
  if(b>7 || b<0){
    return " ";
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


void micSetup(){ //This get's our time we need to wait before taking measurements
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds
}

double getMicFrequency(){ //this takes reading from the microphone and returns to us a frequency
  for(int i = 0; i<SAMPLES; i++){
    microSeconds = micros();   //Returns the amound of micro seconds sense the arduino boatd stated to run
    vReal[i] = analogRead(MICROPHONE);  //Reads the value from analog pin 14 (A0), quantize it and save it as a real term.
    vImag[i] = 0; //Makes imaginary term 0 always

    //remaining wait time between samples if necessary
    while(micros() < (microSeconds+samplingPeriod)){
      //do nothing----THiNK ABOUT LATER
    }
  }
  //THESE three lines of code are completing the FFT calculations for us
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

 // Find prak frequency and print peak
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  return(peak);   
}

float getMuxInput(int channel){
  int controlPin[4] = {MUX_PIN0, MUX_PIN1, MUX_PIN2, MUX_PIN3};

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel(channel,i)); //first par controls the area to change //second par controls the value(high, low) to change first to
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_PIN);
  //return the value
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
    buttons[i] = analogRead(SIG_PIN);//setting each button signifier to a value of high or low
    delay(20);
    Serial.print(analogRead(SIG_PIN));
    Serial.print(F(" : "));
  }
  Serial.println(F("Done"));
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
      if( analogRead(SIG_PIN) != LOW) stillWating = false;
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

//work in progress = finds and returns the closed note to the given pitch as a freq
//If you don't understand how this works, its becuase it doens't
// String closestNote(){
//   //Listen for Freq 
//   double note = getMicFrequency();
//   //Search for the middle area
//   int x =12;
//   int y = 7;
//   bool found = false;
//   if (note > noteArray(x,y)) return "Outside range\nToo high pitch";
//   if (note < noteArray(0,0)) return "Outside range\nToo low pitch";
//   for(y=6;note < noteArray(x,y) && y>0;y--);
//   if(note<noteArray(y+1,0)){
//     if((note - noteArray(y,x)) > (note - noteArray(y+1,0))){
//         return noteArray(y,x);
//     }
//     return  noteArray(y+1,0);
//   }
//   y++;

//   for(x=0;note < noteArray(x,y)*1.03 && x>0;x++);
//   return noteArray(x,y);
// }

int confirmButton(int buttonN){ //makes sure that the button press is correct
    //lcdClear();
    lcdSetCur(0,1);//where we want to print
    lcdPrint("Press and hold (:");
  while(buttonN < 0){ //keep them here until a button of some type goes back
    buttonN = checkForButtonPress(); //this will give an updated value
  }
  return buttonN;
}

int pickingANote(){ // returns the note and the freq we are using
  //make prompt for user
  lcdClear();
  lcdSetCur(0,0);
  lcdPrint("pick a note!");
  //lcdSetCursor(0,1);
  //we need to wait for them to pick some type of note 
  int buttonNum = -1; //We can know when more than one or None are picked
  buttonNum= confirmButton(buttonNum); //sets to the new button once it is correct

  if(buttonNum == 12){//Back Button
    return -1;
  }else if(buttonNum > 12){ //Anything else
    return -2;
  }
  
  return buttonNum;
}

int pickingAOctave(){ // returns the Ocatave and the freq we are using
  //make prompt for user
  lcdClear();
  lcdSetCur(0,0);
  lcdPrint("pick an octave!");
  //lcdSetCursor(0,1);
  //we need to wait for them to pick some type of note 
  int buttonNum = -1; //We can know when more than one or None are picked
  buttonNum= confirmButton(buttonNum); //sets to the new button once it is correct

  if(buttonNum > 7){
    if(buttonNum == 12){//Back Button
      return -1;
    }else{ //Anything else
      return -2;
    }
  }
  return buttonNum;
}

String noteFinder(double freqOfNote){
  int octavePosition = 0;
  int notePosition = 0;

  int ar[12][7]={
/*C*/     {NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6, NOTE_C7},
/*C#Db*/  {NOTE_CS1, NOTE_CS2, NOTE_CS3, NOTE_CS4, NOTE_CS5, NOTE_CS6, NOTE_CS7},
/*D*/     {NOTE_D1, NOTE_D2, NOTE_D3, NOTE_D4, NOTE_D5, NOTE_D6, NOTE_D7},
/*D#Eb*/  {NOTE_DS1, NOTE_DS2, NOTE_DS3, NOTE_DS4, NOTE_DS5, NOTE_DS6, NOTE_DS7},
/*E*/     {NOTE_E1, NOTE_E2, NOTE_E3, NOTE_E4, NOTE_E5, NOTE_E6, NOTE_E7},
/*F*/     {NOTE_F1, NOTE_F2, NOTE_F3, NOTE_F4, NOTE_F5, NOTE_F6, NOTE_F7},
/*F#/Gb*/ {NOTE_FS1, NOTE_FS2, NOTE_FS3, NOTE_FS4, NOTE_FS5, NOTE_FS6, NOTE_FS7},
/*G*/     {NOTE_G1, NOTE_G2, NOTE_G3, NOTE_G4, NOTE_G5, NOTE_G6, NOTE_G7},
/*G#/Ab*/ {NOTE_GS1, NOTE_GS2, NOTE_GS3, NOTE_GS4, NOTE_GS5, NOTE_GS6, NOTE_GS7},
/*A*/     {NOTE_A1, NOTE_A2, NOTE_A3, NOTE_A4, NOTE_A5, NOTE_A6, NOTE_A7},
/*A#Bb*/  {NOTE_AS1, NOTE_AS2, NOTE_AS3, NOTE_AS4, NOTE_AS5, NOTE_AS6, NOTE_AS7},
/*B*/     {NOTE_B1, NOTE_B2, NOTE_B3, NOTE_B4, NOTE_B5, NOTE_B6, NOTE_B7}
  };

  for(int i = 1; i==6; i++){//going through all the notes values to determine location
    if(ar[0][i] > freqOfNote){//check if the freq is less than or greater than the current note to find location
      octavePosition = i-1;
      break;
    }
  }
  for(int i = 1; i==11; i++){//going through all the notes values to determine location
    if(ar[i][octavePosition] > freqOfNote){//check if the freq is less than or greater than the current note to find location
      int lowerP = abs((ar[i-1][octavePosition]/freqOfNote) - 1); //we are checking to see if the one below it or above it is closer to the frequency they are outputing
      int higherP = abs((ar[i][octavePosition]/freqOfNote) - 1);//we subtract one and take the absolute value to see who is closer to 0
      if(lowerP < higherP){
        notePosition = i - 1;
      }else{
        notePosition = i;
      }
      break;
    }
  }

  return noteStrArray(octavePosition, notePosition);
}






