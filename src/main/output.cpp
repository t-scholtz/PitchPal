#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "output.h"  
#include "pinlayout.h" 

//setting up and testing LCD to have it's strings stored in specific adress
//LCD will be a 16 by 2 line display //FIXED THE LINE DISPLAY, were you testing??
LiquidCrystal_I2C lcd(0x27,16,2); 

void initializeLCD(){ //Turns on the LCD, gives the welcome message
  lcd.init();    //lcd.begin(); do these two do differnt things? and did init come from the library?     // initialize the lcd 
  lcd.backlight();
  lcd.print("Welcome to");
  lcd.setCursor(0,1);
  lcd.print("Pitch Pale");
  delay(500); //gives 5 seconds before the system will start the button options
  Serial.println("LCD setup done"); //Testing?
}

void printFreq(double freq){//this should be used for testing //I am going to write the ones for the final output
  lcd.clear();
  lcd.print("Freq is: ");
  lcd.print(freq);
  lcd.print("Hz");
  lcd.setCursor(0,1);
  lcd.print("*\(^o^)/*");
}

void printCFreq(double freq, string note){//This will be printing on the left side of the lcd
  lcd.setCursor(0,0);//prints the updating frequency
  lcd.print("CF:");
  lcd.print(freq)

  lcd.setCursor(0,1);//prints the updating note relating to the frequency
  lcd.print("CN:");
  lcd.print(note); 
}

void printGFreq(double freq, string note){//This will be printing on the right side of the lcd
  lcd.setCursor(8,0);//prints the goal frequency  //WE may need a bigger lcd or play around with these points
  lcd.print("GF:");
  lcd.print(freq)

  lcd.setCursor(8,1);//prints the updating note relating to the frequency
  lcd.print("GN:");
  lcd.print(note); 
}

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