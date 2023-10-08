This



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