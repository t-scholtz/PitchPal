#ifndef PINLAYOUT_H
#define PINLAYOUT_H

#define SAMPLES 128           //The amount of samples we need to calculate frequency and root out most dominant
 //has to be in power of two //This is the max for the arduino uno

#define SAMPLING_FREQUENCY 2048 //This is double the max frequency we need

#define SERIAL_RATE 115200 //The boud rate //rate at which our measurments are taken/updates
#define NOTE_LENGTH 10000

#define SIG_PIN 0
#define SPEAKER 3
#define MUX_PIN0 8
#define MUX_PIN1 9
#define MUX_PIN2 10
#define MUX_PIN3 11
#define MICROPHONE 14

#endif