#ifndef OUTPUT_H
#define OUTPUT_H

void initializeLCD();
void printFreq(double freq);
void lcdClear();
void lcdSetCur(int x, int y);
void lcdPrint(String input);
void playNote(int note, int length);
void startUpAnim();
void starterState();
void printFreq(double freq);
void playNote(int note, int length);
void stageTwoPrompt();
void invalidPrompt();
void noteExamplePrompt();
void listeningPrompt();
void updatingPrompt(double CFeqency, String CNote, double GFrequency, String GNote)
void finisherPrompt();


#endif 