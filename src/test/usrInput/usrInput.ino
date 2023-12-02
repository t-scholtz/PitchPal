#include <Arduino.h>

#define LOW 1000.0


#define ENABLE 6
#define MUX_PIN0 7
#define MUX_PIN1 8
#define MUX_PIN2 9
#define MUX_PIN3 10
#define SIG_PIN 15

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing PitchPal");//Testing 

  pinMode(MUX_PIN0, OUTPUT);
  pinMode(MUX_PIN1, OUTPUT);
  pinMode(MUX_PIN2, OUTPUT);
  pinMode(MUX_PIN3, OUTPUT);

  digitalWrite(MUX_PIN0, LOW);
  digitalWrite(MUX_PIN1, LOW);
  digitalWrite(MUX_PIN2, LOW);
  digitalWrite(MUX_PIN3, LOW);
  Serial.println("Pin layout - Set!");
}

void loop(){
    int buttonPressed = checkForButtonPress();
    Serial.print("Button Pressed: ");
    Serial.println(buttonPressed);
}

int muxChannel(int a, int b){
  int ar[16][4] = {{0,0,0,0}, //channel 0
  {1,0,0,0}, //channel 1
  {0,1,0,0}, //channel 2
  {1,1,0,0}, //channel 3
  {0,0,1,0}, //channel 4
  {1,0,1,0}, //channel 5
  {0,1,1,0}, //channel 6
  {1,1,1,0}, //channel 7
  {0,0,0,1}, //channel 8
  {1,0,0,1}, //channel 9
  {0,1,0,1}, //channel 10
  {1,1,0,1}, //channel 11
  {0,0,1,1}, //channel 12
  {1,0,1,1}, //channel 13
  {0,1,1,1}, //channel 14
  {1,1,1,1}  //channel 15
};
   if(a>16 || a<0){
    return " ";
  }
  if(b>4 || b<0){
    return " ";
  }
  return ar[a][b];

}

int checkForButtonPress(){
  int controlPin[] = {MUX_PIN0, MUX_PIN1, MUX_PIN2, MUX_PIN3};
  float buttons[16];
  //Read from every channel and grab the value at that point of time
  for(int h = 0; h<2 ; h++){
    for(int i = h; i<16 ; i+=2){
      for(int j = 0; j < 4; j ++){
        digitalWrite(controlPin[j], muxChannel(i,j)); //setting each set of pins line by line to read
        //delay(1000);
      }
      buttons[i] = analogRead(SIG_PIN);//setting each button signifier to a value of high or low
      delay(20);
      Serial.print(analogRead(SIG_PIN));
      Serial.print(" : ");
    }
    buttons[i] = analogRead(SIG_PIN);//setting each button signifier to a value of high or low //JUST WITNISSED IN THE SHORT TIME FOR THREE LINES THE ANALOG READ CAN BE DRAMATICALLY DIFFERNT
    delay(40);
    Serial.print(analogRead(SIG_PIN));
    Serial.print(" : ");

  }
  Serial.println("Done");
  delay(1000);
  //Flag will count how many channels have high value - more than one indicates that 2 or more buttons pressed at same time which will return -1
  int flag = 0;
  int output = 0;
  for(int i = 0; i<16 ; i++){//runs 16 times, stops at 16
  delay(100);
  Serial.println(buttons[i]);
    if (buttons[i] > LOW ){
      flag++;
      output = i;
    }
  }
  Serial.println("OUTPUT: ");
  Serial.println(flag);
  if (flag == 1){
    return output;
    }
  else if(flag > 1){
    return -1;
  }

  return -1;//return the button number
}