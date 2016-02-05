/*
  State change detection (edge detection)
 	
 Often, you don't need to know the state of a digital input all the time,
 but you just need to know when the input changes from one state to another.
 For example, you want to know when a button goes from OFF to ON.  This is called
 state change detection, or edge detection.
 
 This example shows how to detect when a button or button changes from off to on
 and on to off.
 	
 The circuit:
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 * LED attached from pin 13 to ground (or use the built-in LED on
   most Arduino boards)
 
 created  27 Sep 2005
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 	
 http://arduino.cc/en/Tutorial/ButtonStateChange
 
 Modified to read and compare two button inputs for arm wrestling game.
 
 modified 27 Feb 2014
 by Brent Hornilla

 */

// this constant won't change:
const int  buttonPin1 = 2;    // the pin that the first player pushbutton is attached to
const int  buttonPin2 = 3;    // the pin that the second player pushbotton is attached to
// const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter1 = 0;   // counter for the number of button presses
int buttonPushCounter2 = 0;
int buttonState1 = 0;         // current state of the button
int buttonState2 = 0;
int lastButtonState1 = 0;     // previous state of the button
int lastButtonState2 = 0;
int rate1 = 0;                // rate thate buttons are pressed
int rate2 = 0;

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  for(int i=0 ; i<10 ; i++)
  {
  // read the pushbutton inputs:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  
  // compare buttonState1 to its previous state
  if (buttonState1 != lastButtonState1) {
    // if the state has changed, increment the counter
    if (buttonState1 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter1++;
      // Serial.println("on");
      // Serial.print("number of button pushes:  ");
      // Serial.println(buttonPushCounter1);
    } 
    else {
      // if the current state is LOW then the button
      // went from on to off:
      // Serial.println("off"); 
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState1 = buttonState1;

  // compare the buttonState2 to its previous state
  if (buttonState2 != lastButtonState2) {
    // if the state has changed, increment the counter
    if (buttonState2 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter2++;
      // Serial.println("on");
      // Serial.print("number of button pushes:  ");
      // Serial.println(buttonPushCounter2);
    } 
    else {
      // if the current state is LOW then the button
      // went from on to off:
      // Serial.println("off"); 
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState2 = buttonState2;
  
  // turns on the LED every four button pushes by 
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of 
  // the division of two numbers:
  // if (buttonPushCounter % 4 == 0) {
  //   digitalWrite(ledPin, HIGH);
  // } else {
  // digitalWrite(ledPin, LOW);
  // }
  
  delay(100);
  }
  
  rate1 = buttonPushCounter1/10;
  rate2 = buttonPushCounter2/10;
  
}
