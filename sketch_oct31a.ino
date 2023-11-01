#include "arduinoFFT.h"
#include "LiquidCrystal_I2C.h"

#define SAMPLES 128   //How many points you FFT will have  //Must be a base 2 number  //MAX 128 or less for the arduino uno
#define SAMPLING_FREQUENCY 2048 //This number must be 2 times the highest frequency expected 

arduinoFFT FFT = arduinoFFT();

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES]; //creates vector/array of size SAMPLES to hold real values
double vImag[SAMPLES]; // creates vector/array of size SAMPLES to hold imaginary values


void setup() {
  Serial.begin(115200); //baud rate for the serial Monitor
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds
}

void loop() {
  for(int i = 0; i<SAMPLES; i++){
    microSeconds = micros();   //Returns the amound of micro seconds sense the arduino boatd stated to run

    vReal[i] = analogRead(14);  //Reads the value from analog pin 14 (A0), quantize it and save it as a real term.
    vImag[i] = 0; //Makes imaginary term 0 always

    //remaining wait time between samples if necessary
    while(micros() < (microSeconds+samplingPeriod)){
      //do nothing
    }
  }
  //THESE three lines of code are completing the FFT calculations for us
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  //Find prak frequency and print peak
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  Serial.println(peak);   //print out the most dominant frequency

  //Script stops here. Hardware reset Required
  //while(1);//do one time
}