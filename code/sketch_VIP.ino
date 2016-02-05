/*
Refactored Code for Arm Wrestling Robot
Georgia Tech Institute of Technology
VIP I-Natural
Spring 2014

Members
Hardware: Christina, Alexis, Karan, Rem
Software: Zhou, Asha, Brent, Michael

Created 2/27/20014
Last Modified 3/27/2014 by Michael Kuchnik
*/

#include <Servo.h>
#include <Arduino.h>
#include "Game.h"
#include "Machine.h"
#include "Person.h"

enum gameState {
    INITIALSTATE = 0,
    STARTSTATE = 1,
    GAMEPLAYSTATE = 2,
    GAMEOVERSTATE = 3
};

void setup() { }

Machine _arduino(9, 10, 11, 12, 13, 2, 3, 4, 5, 13, 12);
Person _player1(1);
Person _player2(1);
Game _game(_arduino, _player1, _player2, 0, 0);

//FIX: rates not reset
int rate1 = 1;                // rates thate buttons are pressed
int rate2 = 1;
int buttonState1;         // current state of the button
int buttonState2;


// loop routine runs indefinitely
void loop() {
    for(int i=0 ; i<1000 ; i++)
    {
      // read the pushbutton inputs:
      buttonState1 = _arduino.getButtonPin1();
      buttonState2 = _arduino.getButtonPin2();
  
      // compare buttonState1 to its previous state
      if (buttonState1 != _game.getLastButton1()) {
        // if the state has changed, increment the counter
        if (buttonState1 == HIGH) {
          // if the current state is HIGH then the button
          // went from off to on:
          _game.setPushButtonCounter1(_game.getPushButtonCounter1() + 1);
        }
      }
      
      // save the current state as the last state
       _game.setLastButton1(buttonState1);

      // compare the buttonState2 to its previous state
      if (buttonState2 != _game.getLastButton2()) {
        // if the state has changed, increment the counter
        if (buttonState2 == HIGH) {
          // if the current state is HIGH then the button
          // went from off to on:
          _game.setPushButtonCounter2(_game.getPushButtonCounter2() + 1);
        }
      }
      
      // save the current state as the last state
       _game.setLastButton2(buttonState2);
  
      delay(1);
    }
    
    // calculate bias ratios
    rate1 =_game.getPushButtonCounter1()/10;
    rate2 =_game.getPushButtonCounter2()/10;
    _game.setBias(rate1, rate2);
    _game.setCurrentState(STARTSTATE);
}
   

