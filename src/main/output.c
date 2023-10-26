#include "output.h"  
#include "pinlayout.h" 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//setting up and testing LCD to have it's strings stored in specific adress
//LCD will be a 16 by 2 line display
LiquidCrystal_I2C lcd( 0x27, 16, 2);

void setup() {
  //start up the LCD
  lcd.begin();

  //initialize the serial monitor
  //This sets the baud rate -> rate of communication is bits per second
  Serial.begin(9600);

  //Turn on backlight
  lcd.backlight();

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("robojax");
  lcd.setCursor(0,1); //goes to the start of the 2nd line //PLAY AROUND WITH THIS ONE
  lcd.print("Hello World!");
  delay(500);
  lcd.clear();
  delay(500);


}
