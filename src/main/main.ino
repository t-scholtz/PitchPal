gi//TODO - UPDATE HEADER

/*********************************************/
/* Name of the program: */
/* Author: Timothy Scholtz */
/* C program file name: */
/* Compile command: gcc TimothyScholtz_FuncCE.c -o run */
/* Run using: ./run */
/* Date: 10/6/2023 */
/*********************************************/



int ButtonValue = 0;

int BUTTON = 3;
int LED = 2;

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);

}

void loop() {
  ButtonValue = digitalRead(BUTTON);

  if (ButtonValue != 0){
      digitalWrite(LED, HIGH);
  }
  else{
      digitalWrite(LED, LOW);
  }

}