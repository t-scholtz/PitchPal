#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

LiquidCrystal_I2C lcd(0x27,16,2); 

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  //Speacial Chars for Fun
  uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
  uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
  uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
  uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
  uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
  uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
  uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
  uint8_t retarrow[8] = {	0x1,0x1,0x5,0x9,0x1f,0x8,0x4};
  lcd.createChar(0, bell);
  lcd.createChar(1, note);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);
  lcd.home();
}

void loop(){
  char pitchPal[] = {'p','i','t','c','h','P','a','l',' ',' ','b','e','t','a',' ','1',' '};
    for(int i = 0;i<16;i++ ){
      lcd.setCursor( i+1,0);
      lcd.printByte(1);
      lcd.setCursor(0, 1);
      for(int j = 0; j<i;j++){
        lcd.print(pitchPal[j]);
      }
      delay(500);
      lcd.clear();
    }  
}