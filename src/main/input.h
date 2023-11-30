// input.h
#ifndef INPUT_H
#define INPUT_H

String noteToString(int note);
int noteArray(int a, int b);
String noteStrArray(int a, int b);
int muxChannel(int a, int b);
float getMuxInput(int channel);
void micSetup();
double getMicFrequency();
int checkForButtonPress();
int waitForUserInput();
int waitScrollingText(String text);
int selectNote();
int selectOctave();
String noteFinder(double freqOfNote);
#endif