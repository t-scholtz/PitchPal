#ifndef OUTPUT_H
#define OUTPUT_H

void initializeLCD();
void lcdClear();
void lcdSetCur(int x, int y);
void lcdPrint(String A, String B);
void playNote(int note, int length);
void startUpAnim();

#endif 