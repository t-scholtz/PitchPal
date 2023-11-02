#include <Arduino.h>
#include <Wire.h>
#include "output.h"  
#include "pinlayout.h" 
#include "LiquidCrystal_I2C.h"


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
   Serial.println("LCD setup done");
}

void printFreq(double freq){
  lcd.clear();
  lcd.print("Freq is: ");
  lcd.print(freq);
  lcd.print("Hz");
  lcd.setCursor(0,1);
  lcd.print("*\(^o^)/*");
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
void lcdPrint(String input){
  lcd.clear();
  lcd.print(input);
}

void lcdClear(){ 
  lcd.clear();
}

void playNote(int note, int length){ //this one should be relitivly simple 
    int noteDuration = NOTE_LENGTH / length;
    tone(SPEAKER, note, noteDuration);
    delay(noteDuration);
    // // to distinguish the notes, set a minimum time between them.
    // // the note's duration + 30% seems to work well:
    // int pauseBetweenNotes = noteDuration * 1.30;
    // delay(pauseBetweenNotes);
    noTone(SPEAKER);
}