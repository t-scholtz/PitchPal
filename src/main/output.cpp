#include <Arduino.h>
#include "output.h"  
#include "pinlayout.h" 
#include "LiquidCrystal_I2C.h"
#include <Wire.h>

//setting up and testing LCD to have it's strings stored in specific adress
//LCD will be a 16 by 2 line display
LiquidCrystal_I2C lcd( 0x27, 16, 2);

void initializeLCD(){
  lcd.begin();
}

void toggleBackligh(){
  //This use to turn on backlight, not sure if calling twice will turn on then off
  lcd.backlight();
}

void testProcedure(){
  lcd.clear();
  lcd.print("robojax");
  lcd.setCursor(0,1); //goes to the start of the 2nd line //PLAY AROUND WITH THIS ONE
  lcd.print("Hello World!");
  delay(500);
  lcd.clear();
  delay(500);
}

