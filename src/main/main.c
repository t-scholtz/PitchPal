//TODO - UPDATE HEADER

/*********************************************/
/* Name of the program: */
/* Author: Timothy Scholtz ; Thomoas Mahok */
/* C program file name: */
/* Date: 10/6/2023 */
/*********************************************/

// To play from speaker use tone(SPEAKER, melody[thisNote], noteDuration);
// stop the tone playing: noTone(SPEAKER)

#include "pinlayout.h" 
#include "input.h" 
#include "output.h" 

void setup() {
  pinMode(MUX0, OUTPUT);
  pinMode(MUX1, OUTPUT);
  pinMode(MUX2, OUTPUT);
  pinMode(MUX3, OUTPUT);

  digitalWrite(MUX0, LOW);
  digitalWrite(MUX1, LOW);
  digitalWrite(MUX2, LOW);
  digitalWrite(MUX3, LOW);

  Serial.begin(9600);
}

void loop() {
 for(int i = 0; i < 16; i ++){
    Serial.print("Value at channel ");
    Serial.print(i);
    Serial.print("is : ");
    Serial.println(readMux(i));
    delay(1000);
  }
}

