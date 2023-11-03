#include <Arduino.h>
#include <arduinoFFT.h>

#include "input.h"  
#include "pinlayout.h" 

#define LOW 1.0

arduinoFFT FFT = arduinoFFT();
unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES]; //creates vector/array of size SAMPLES to hold real values
double vImag[SAMPLES]; // creates vector/array of size SAMPLES to hold imaginary values

int muxChannel[16][4]={
  {0,0,0,0}, //channel 0
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

void micSetup(){ //This get's our time we need to wait before taking measurements
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds
}

double getMicFrequency(){
  for(int i = 0; i<SAMPLES; i++){
    microSeconds = micros();   //Returns the amound of micro seconds sense the arduino boatd stated to run
    vReal[i] = analogRead(MICROPHONE);  //Reads the value from analog pin 14 (A0), quantize it and save it as a real term.
    vImag[i] = 0; //Makes imaginary term 0 always

    //remaining wait time between samples if necessary
    while(micros() < (microSeconds+samplingPeriod)){
      //do nothing ----------------- may need to optimise later -----We could try to take it out
      //When we first tried this we were trying to calculate it and it was giving us problems with the mod calculations right??
    }
  }
  //THESE three lines of code are completing the FFT calculations for us
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  //Find prak frequency and print peak
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  return(peak);   
}


float getMuxInput(int channel){
  int controlPin[] = {MUX_PIN0, MUX_PIN1, MUX_PIN2, MUX_PIN3};

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]); //first par controls the area to change //second par controls the value(high, low) to change first to
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_PIN);
  //return the value
  float voltage = (val * 5.0) / 1024.0; 
  return voltage; //Does this voltage give us the number for the input to translate?
}


//Will return an number -1 to 15 with -1 meaning 2 or buttons were detected being pressed at the same
int checkForButtonPress(){
  int controlPin[] = {MUX_PIN0, MUX_PIN1, MUX_PIN2, MUX_PIN3};
  float buttons[16];
  //Read from every channel and grab the value at that point of time
  for(int i = 0; i<16 ; i++){
    for(int j = 0; j < 4; j ++){
      digitalWrite(controlPin[j], muxChannel[i][j]); //setting each set of pins line by line to read //IS THE control pin telling the pins where to read from???
    }
    buttons[i] = analogRead(SIG_PIN);//setting each button to a value of high or low
  }
  //Flag will count how many channels have high value - more than one indicates that 2 or more buttons pressed at same time which will return -1
  int flag = 0;
  int output = -1;
  for(int i = 0; i<16 ; i++){ //I think this will count 17 buttons, same with the two forloops above, if you want to add first i think it is ++i(NOTE: look into sysntax)
    if (buttons[i] > LOW ){
      flag++;
      output = i; //is output for testing purposes?? //NOTE tell time when he is testing something to put a testing comment
    }
  }
  if (flag != 1) return -1;
  return output;//return the button number
}
