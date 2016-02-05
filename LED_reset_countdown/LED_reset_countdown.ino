// LED Pins
const int led1 = 2;
const int led2 = 4;
const int led3 = 7;

//Reset Button Setup
const int startButton = 12;
const int reset = 13;

int buttonState = 0;         // variable for reading the pushbutton status


void setup() 
{
  // initialize the LEDs as output:
  pinMode(led1, OUTPUT);  
  pinMode(led2, OUTPUT);  
  pinMode(led3, OUTPUT);    
  // initialize the pushbutton pin as an input:
  pinMode(startButton, INPUT);     
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(startButton);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LEDs on:    
    digitalWrite(led1, HIGH); 
    delay(750);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(750); 
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    delay(750); 
  } 
  else {
    // turn LED off:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW); 
  }
}
