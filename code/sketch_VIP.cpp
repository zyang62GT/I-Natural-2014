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

// loop routine runs indefinitely
void loop() {
	_game.updateState();
}
   

