// input.h
#ifndef INPUT_H
#define INPUT_H

int noteArray(int a, int b);
String noteStrArray(int a, int b);
int muxChannel(int a, int b);
float getMuxInput(int channel);
void micSetup();
double getMicFrequency();
int checkForButtonPress();
int waitForUserInput();
String closestNote();
int pickingANote();
int pickingAOctave();
int confirmButton(int buttonN);
String noteFinder(double freqOfNote);

#endif