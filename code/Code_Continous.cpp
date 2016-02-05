/*
Continuous code for Arm Wrestling Robot
Georgia Tech Institute of Technology
VIP I-Natural
Spring 2014

Members
Hardware: Christina, Alexis, Karan, Rem
Software: Zhou, Asha, Brent, Michael

Created 2/27/20014
Last Modified 4/3/2014 by Brent Hornilla

CODE OUTLINE:

State = Start
Loop{

If Init {
 Read inputs for 10 seconds to calibrate
 Calculate bias ratio
 Switch state to Start
}
Else Game Start{
 Wait
 If Reset is pressed, switch state to Init
 If Play is pressed, switch state to Play
 ~ LCD display for Game Start and W/L record
}
Else Play{
 Apply bias to button rates and apply as force to servos
 Run until win detected
 Switch state to Game Over
 ~ LCD display for Play and W/L record
}
Else Game Over{
 Wait
 If Reset is pressed, switch state to Init
 If Start is pressed, switch state to Start 
 ~ LCD display for player winner and W/L record
}
End If

CHANGELOG:

}  

}End Loop
*/

#include <Servo.h>

// initialize leds and pushbutton pins
const int led5 = 8;
const int led4 = 6;
const int led3 = 7;
const int led2 = 4;
const int led1 = 2;
const int StartButtonPin = 12; // the Start button pin#
const int ResetButtonPin = 13; // the Reset button pin#
const int buttonPin1 = 3;     // the pin that the first player pushbutton is attached to
const int buttonPin2 = 5;     // the pin that the second player pushbotton is attached to
const int Motor1Control = 9; // the player 1 motor pin#
const int Motor2Control = 10; // the player 2 motor pin#
Servo myservo1;
Servo myservo2;

// initialize states, Init, Start, Game Play, Game over
const int InitialState = 0;
const int StartState = 1;
const int GamePlayState= 2;
const int GameOverState= 3;

int CounterStart = 0;
int StartButtonState = 0;
int ResetButtonState = 0;
int CurrentState=StartState;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output:
  pinMode(led5, OUTPUT);
  pinMode(led4, OUTPUT);  
  pinMode(led3, OUTPUT);  
  pinMode(led2, OUTPUT);  
  pinMode(led1, OUTPUT);  

  // initialize the button pins as inputs:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT); 
  pinMode(StartButtonPin, INPUT);  
  pinMode(ResetButtonPin, INPUT);

  // initialize servo controls
  myservo1.attach(Motor1Control);
  myservo2.attach(Motor2Control);

  // initialize serial communication:
  Serial.begin(9600);
}

// Variables will change:
int buttonPushCounter1 = 0;   // counter for the number of button presses
int buttonPushCounter2 = 0;
int buttonState1 = 0;         // current state of the button
int buttonState2 = 0;
int lastButtonState1 = 0;     // previous state of the button
int lastButtonState2 = 0;
int rate1 = 1;                // rates thate buttons are pressed
int rate2 = 1;
int bias1 = 1;                // bias ratios
int bias2 = 1;
int increment = 0;            // arm position

// loop routine runs indefinitely
void loop() {
  
  // Initial State
  if (CurrentState == InitialState){
    Serial.println("Initial State");
    buttonPushCounter1 = 0;  // reset for calibration
    buttonPushCounter2 = 0;
    lastButtonState1 = 0;
    lastButtonState2 = 0;
    
    for(int i=0 ; i<10000 ; i++)
    {
      // read the pushbutton inputs:
      buttonState1 = digitalRead(buttonPin1);
      buttonState2 = digitalRead(buttonPin2);
  
      // compare buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button
          // went from off to on:
          buttonPushCounter1++;
        }
      }
      
      // save the current state as the last state
      lastButtonState1 = buttonState1;

      // compare the buttonState2 to its previous state
      if (buttonState2 != lastButtonState2) {
        // if the state has changed, increment the counter
        if (buttonState2 == HIGH) {
          // if the current state is HIGH then the button
          // went from off to on:
          buttonPushCounter2++;
        }
      }
      
      // save the current state as the last state
      lastButtonState2 = buttonState2;
  
      delay(1);
    }
    
    // calculate bias ratios
    rate1 = buttonPushCounter1/10;
    rate2 = buttonPushCounter2/10;
    bias1 = rate2/rate1;
    bias2 = rate1/rate2;
    CurrentState = StartState;
  }
  
  // Start State
  else if (CurrentState == StartState){
    Serial.println("Start State");
    // check start button input
    StartButtonState=digitalRead(StartButtonPin);
    if(StartButtonState == HIGH){
      digitalWrite(led5, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led1, HIGH);
      
      // countdown from Start to Play
      CounterStart = 0;
      while (CounterStart<=5){
        if(CounterStart == 1){
          digitalWrite(led5, LOW);
        } 
        if(CounterStart == 2){
          digitalWrite(led4, LOW);
        } 
        if(CounterStart == 3){
          digitalWrite(led3, LOW);
        } 
        if(CounterStart == 4){
          digitalWrite(led2, LOW);
        } 
        if(CounterStart == 5){
          digitalWrite(led1, LOW);
        } 
        CounterStart=CounterStart+1;
        delay(1000);
      }
      CurrentState = GamePlayState;
      
    }
    
    // check reset button input
    ResetButtonState=digitalRead(ResetButtonPin);
    if(ResetButtonState == HIGH){
      digitalWrite(led5, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led1, HIGH);
      
      // countdown from Game Over to Initial
      CounterStart = 0;
      while (CounterStart<=5){
        if(CounterStart == 1){
          digitalWrite(led5, LOW);
        } 
        if(CounterStart == 2){
          digitalWrite(led4, LOW);
        } 
        if(CounterStart == 3){
          digitalWrite(led3, LOW);
        } 
        if(CounterStart == 4){
          digitalWrite(led2, LOW);
        } 
        if(CounterStart == 5){
          digitalWrite(led1, LOW);
        } 
        CounterStart=CounterStart+1;
        delay(1000);
      }
      CurrentState = InitialState;
    }
    
  }   
  
  // Play State
  else if (CurrentState == GamePlayState){
    Serial.println("Play State");
    lastButtonState1 = 0;          // reset for game play
    lastButtonState2 = 0;
    
    for(increment = 0 ; abs(increment)<33 ; )
    {
      // read the pushbutton inputs:
      buttonState1 = digitalRead(buttonPin1);
      buttonState2 = digitalRead(buttonPin2);
  
      // compare buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button
          // went from off to on:
          increment += bias1;
        }
      }
      
      // save the current state as the last state
      lastButtonState1 = buttonState1;

      // compare the buttonState2 to its previous state
      if (buttonState2 != lastButtonState2) {
        // if the state has changed, increment the counter
        if (buttonState2 == HIGH) {
          // if the current state is HIGH then the button
          // went from off to on:
          increment += -bias2;
        }
      }
      
      // save the current state as the last state
      lastButtonState2 = buttonState2;
      myservo1.write(int(32.5+increment));
      myservo2.write(75-int(32.5+increment));
    }

    // check which of the players won
    if(int(32.5+increment)>=75){
      // player 1 win
      CurrentState = GameOverState;
    }
    else if (int(32.5+increment)<=0){
      // player 2 win
      CurrentState = GameOverState;
    }
  }
  
  // Game Over State
  else if (CurrentState == GameOverState){
    Serial.println("Game Over State");
    StartButtonState=digitalRead(StartButtonPin);
    if(StartButtonState == HIGH){
      CurrentState = StartState;
    }
    
    ResetButtonState=digitalRead(ResetButtonPin);
    if(ResetButtonState == HIGH){
      digitalWrite(led5, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led1, HIGH);
      
      CounterStart = 0;
      // Countdown from Game Over to Initial
      while (CounterStart<=5){
        if(CounterStart == 1){
          digitalWrite(led5, LOW);
        } 
        if(CounterStart == 2){
          digitalWrite(led4, LOW);
        } 
        if(CounterStart == 3){
          digitalWrite(led3, LOW);
        } 
        if(CounterStart == 4){
          digitalWrite(led2, LOW);
        } 
        if(CounterStart == 5){
          digitalWrite(led1, LOW);
        } 
        CounterStart=CounterStart+1;
        delay(1000);
      }
      CurrentState = InitialState;
    }
  }
  
}
