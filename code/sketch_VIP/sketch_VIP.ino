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
#include "Game.h"
#include "Machine.h"
#include "Person.h"

enum gameState {
    INITIALSTATE = 0,
    STARTSTATE = 1,
    GAMEPLAYSTATE = 2,
    GAMEOVERSTATE = 3
};

const int led5 = 0;
const int led4 = 0;
const int led3 = 7;
const int led2 = 4;
const int led1 = 2;
const int StartButtonPin = 12; // the Start button pin#
const int ResetButtonPin = 8; // the Reset button pin#
const int buttonPin1 = 3;     // the pin that the first player pushbutton is attached to
const int buttonPin2 = 5;     // the pin that the second player pushbotton is attached to
const int Motor1Control = 9; // the player 1 motor pin#
const int Motor2Control = 10; // the player 2 motor pin#
const Servo myservo1;
const Servo myservo2;

Machine _arduino(led1, led2, led3, led4, led5, StartButtonPin, ResetButtonPin, buttonPin1, buttonPin2, Motor1Control, Motor2Control);

void setup() { 
  _arduino.initializePins();
}
  Person _player1(1);
  Person _player2(1);
  Game _game(_arduino, _player1, _player2, 0, 0);
// loop routine runs indefinitely
void loop() {
//   _game.led_init();
   _game.updateState();
   _game.printStateDeltas();
}
   

