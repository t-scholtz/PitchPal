#include <Arduino.h>

#define LOW 0
#define HIGH 1
#define RED 12
#define YELLOW 13
#define GREEN 14

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW); 
}

void loop(){
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH); 
  delay(3000);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, LOW); 
  delay(3000);
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, LOW); 
  delay(3000);    
}