#include <Arduino.h>
#include <arduinoFFT.h>
#include <Wire.h> 

#define A3 220
#define SAMPLES 128   
#define SAMPLING_FREQUENCY 2048 
#define SERIAL_RATE 115200
#define SIG_PIN 0

#define MICROPHONE 14

arduinoFFT FFT = arduinoFFT();
unsigned int samplingPeriod;
unsigned long microSeconds;
double vReal[SAMPLES]; //creates vector/array of size SAMPLES to hold real values
double vImag[SAMPLES];

void setup() {
    Serial.begin(SERIAL_RATE);
    Serial.println("Testing Frequency Check");//Testing 
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));
}

void loop(){
    for(int i = 0; i<SAMPLES; i++){
    microSeconds = micros();   //Returns the amound of micro seconds sense the arduino boatd stated to run
    vReal[i] = analogRead(MICROPHONE);  //Reads the value from analog pin 14 (A0), quantize it and save it as a real term.
    vImag[i] = 0; //Makes imaginary term 0 always
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
  Serial.print("Mesured Frequency: ");
  Serial.println(peak);
  double howClose= peak/A3;

  Serial.print("How close to note: ");
  Serial.println(howClose);
  delay(1000);
}