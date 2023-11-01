#include <Arduino.h>
#include "output.h"  
#include "pinlayout.h" 
#include "LiquidCrystal_I2C.h"
#include <Wire.h>

//setting up and testing LCD to have it's strings stored in specific adress
//LCD will be a 16 by 2 line display
LiquidCrystal_I2C lcd( 0x27, 16, 2);

void initializeLCD(){ //This function turns on the LCD and gives the welcome message
  lcd.begin();
  lcd.backlight();
  lcd.print("  Welcome to");
  lcd.setCursor(0,1);
  lcd.print("  Pitch Pale");
  delay(500); //gives 5 seconds before the system will start the button options
}

void printFreq(double freq){
  lcd.clear();
  lcd.print("Freq is: ");
  lcd.print(freq);
  lcd.print("Hz");
}

// void testProcedure(){ //This function is meant to test the functionality of the LCD
//   lcd.clear();
//   lcd.print("robojax");
//   lcd.setCursor(0,1); //goes to the start of the 2nd line //PLAY AROUND WITH THIS ONE
//   lcd.print("Hello World!");
//   delay(500);
//   lcd.clear();
//   delay(500);
// }

void lcdClear(){ 
  lcd.clear();
}

void speaker_example(){ //this one should be relitivly simple 
  delay(10);
}