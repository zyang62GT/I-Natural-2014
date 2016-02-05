/*
Continuous code for Arm Wrestling Robot
Georgia Tech Institute of Technology
VIP I-Natural
Spring 2014

Members
Hardware: Christina, Alexis, Karan, Rem
Software: Zhou, Asha, Brent, Michael

Created 2/27/20014
Last Modified 4/17/2014 by Brent Hornilla

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
const int led5 = 13;
const int led4 = 13;
const int led3 = 7;
const int led2 = 4;
const int led1 = 2;
const int StartButtonPin = 12; // the Start button pin#
const int ResetButtonPin = 8; // the Reset button pin#
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
int starttime = 0;
int endtime = 0;
float increment = 0.0;            // arm position
float rate1 = 1.0;                // rates thate buttons are pressed
float rate2 = 1.0;
float bias = 1.0;

// loop routine runs indefinitely
void loop() {
  
  // Initial State
  if (CurrentState == InitialState){
    Serial.println("Initial State: Start Calibrating");
    buttonPushCounter1 = 0;  // reset for calibration
    buttonPushCounter2 = 0;
    lastButtonState1 = 0;
    lastButtonState2 = 0;
    starttime = millis();
    endtime = starttime;
    myservo1.write(34);
    myservo2.write(34);
    while((endtime - starttime) <= 10000)
    {
      Serial.println("Calibrating");
      // read the pushbutton inputs:
      buttonState1 = digitalRead(buttonPin1);
      buttonState2 = digitalRead(buttonPin2);
  
      if( digitalRead(ResetButtonPin) == HIGH)
      {
        Serial.println("Reset Pressed");
        break;
      }
  
      // compare buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button
          // went from off to on:
          Serial.println("Button 1 Pressed");
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
          Serial.println("Button 2 Pressed");
          buttonPushCounter2++;
        }
      }
      
      // save the current state as the last state
      lastButtonState2 = buttonState2;
  
      endtime = millis();
    }
    
    // calculate bias ratio
    rate1 = 1000*buttonPushCounter1/(endtime-starttime);
    rate2 = 1000*buttonPushCounter2/(endtime-starttime);
    bias = float(buttonPushCounter2)/float(buttonPushCounter1);
    if(bias>6){
        bias=6; 
    }
    else if(bias < 1/6){
        bias=1/6;
    }
    myservo1.write(34);
    myservo2.write(34);
    Serial.println(buttonPushCounter2);
    Serial.println(buttonPushCounter1);
    Serial.println(bias);
    CurrentState = StartState;
  }
  
  // Start State
  else if (CurrentState == StartState){
    Serial.println("Start State");
    myservo1.write(34);
    myservo2.write(34);
    
    while (digitalRead(StartButtonPin)==LOW&&digitalRead(ResetButtonPin)==LOW)
    {
    }
    // check start button input
    ResetButtonState=digitalRead(ResetButtonPin);
    StartButtonState=digitalRead(StartButtonPin);
    myservo1.write(34);
    myservo2.write(34);
    if(StartButtonState == HIGH){
      myservo1.write(34);
      myservo2.write(34);
      Serial.println("Start Pressed, Countdown to Play");
      digitalWrite(led5, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led1, HIGH);
      
      // countdown from Start to Play
      starttime = millis();
      endtime = starttime;
      while ((endtime - starttime) < 5001){
        if((endtime - starttime) >= 1000){
          digitalWrite(led5, LOW);
        } 
        if((endtime - starttime) >= 2000){
          digitalWrite(led4, LOW);
        } 
        if((endtime - starttime) >= 3000){
          digitalWrite(led3, LOW);
        } 
        if((endtime - starttime) >= 4000){
          digitalWrite(led2, LOW);
        } 
        if((endtime - starttime) >= 5000){
          digitalWrite(led1, LOW);
        } 
        endtime = millis();  
      }
      CurrentState = GamePlayState;
    }

    // check reset button input
    else if(ResetButtonState == HIGH){
      myservo1.write(34);
      myservo2.write(34);
      Serial.println("Reset Pressed, Countdown to Initial");
      digitalWrite(led5, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led1, HIGH);
      
      // countdown from Game Over to Initial
      starttime = millis();
      endtime = starttime;
      while ((endtime - starttime) < 3001){
        if((endtime - starttime) >= 1000){
          digitalWrite(led3, LOW);
        } 
        if((endtime - starttime) >= 2000){
          digitalWrite(led2, LOW);
        } 
        if((endtime - starttime) >= 3000){
          digitalWrite(led1, LOW);
        } 
        endtime = millis();  
      }
      CurrentState = InitialState;
    }
    
  }   
  
  // Play State
  else if (CurrentState == GamePlayState){
    Serial.println("Play State");
    lastButtonState1 = 0;          // reset for game play
    lastButtonState2 = 0;
    Serial.println(increment);
    while(abs(increment)<34)
    {
      // read the pushbutton inputs:
      buttonState1 = digitalRead(buttonPin1);
      buttonState2 = digitalRead(buttonPin2);
      
      if( digitalRead(ResetButtonPin) == HIGH)
      {
        Serial.println("Reset Pressed");
        break;
      }
  
      // compare buttonState1 to its previous state
      if (buttonState1 != lastButtonState1) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button
          // went from off to on:
          Serial.println("Button 1 Pressed");
          if(bias>=1){
              increment += bias;
          }
          else{
              increment+=1;
          }
          
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
          Serial.println("Button 2 Pressed");
          if(bias>=1){
              increment += -1;
          }
          else{
              increment += -1/bias; 
          }
          
        }
      }
      
      // save the current state as the last state
      lastButtonState2 = buttonState2;
      
      myservo1.write(int(34+increment));
      Serial.println(int(34+increment));
      myservo2.write(int(61-(34+increment)));
      //delay(15);
    }

    // check which of the players won
    if(increment>0){
      // player 1 win
      Serial.println("Player 1 Win");
      Serial.println(increment);
      CurrentState = GameOverState;
    }
    else if (increment<0){
      // player 2 win
      Serial.println("Player 2 Win");
      Serial.println(increment);
      CurrentState = GameOverState;
    }
  }
  
  // Game Over State
  else if (CurrentState == GameOverState){
    Serial.println("Game Over");
    while ((digitalRead(StartButtonPin)&digitalRead(ResetButtonPin))==0)
    {
    }
    
    // check start button
    StartButtonState=digitalRead(StartButtonPin);
    if(StartButtonState == HIGH){
      Serial.println("Start Pressed, Countdown to Play");
      digitalWrite(led5, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led1, HIGH);
      
      // Countdown from Game Over to Play
      starttime = millis();
      endtime = starttime;
      while ((endtime - starttime) < 5001){
        if((endtime - starttime) >= 1000){
          digitalWrite(led5, LOW);
        } 
        if((endtime - starttime) >= 2000){
          digitalWrite(led4, LOW);
        } 
        if((endtime - starttime) >= 3000){
          digitalWrite(led3, LOW);
        } 
        if((endtime - starttime) >= 4000){
          digitalWrite(led2, LOW);
        } 
        if((endtime - starttime) >= 5000){
          digitalWrite(led1, LOW);
        } 
        endtime = millis();  
      }
      CurrentState = GamePlayState; 
    }
    
    // check reset button
    ResetButtonState=digitalRead(ResetButtonPin);
    if(ResetButtonState == HIGH){
      Serial.println("Reset Pressed, Countdown to Initial");
      digitalWrite(led5, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led1, HIGH);
      
      // Countdown from Game Over to Initial
      starttime = millis();
      endtime = starttime;
      while ((endtime - starttime) < 5001){
        if((endtime - starttime) >= 1000){
          digitalWrite(led5, LOW);
        } 
        if((endtime - starttime) >= 2000){
          digitalWrite(led4, LOW);
        } 
        if((endtime - starttime) >= 3000){
          digitalWrite(led3, LOW);
        } 
        if((endtime - starttime) >= 4000){
          digitalWrite(led2, LOW);
        } 
        if((endtime - starttime) >= 5000){
          digitalWrite(led1, LOW);
        } 
        endtime = millis();  
      }
      CurrentState = InitialState;
    }
  }
  
}
