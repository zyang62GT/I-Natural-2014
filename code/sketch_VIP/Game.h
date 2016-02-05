#pragma once
#include "Machine.h"
#include "Person.h"

/** 
 * This class represents the game and controls all interactions between Machine and Persons.
 */
class Game {
private:
        enum gameState {
	    INITIALSTATE = 0,
	    STARTSTATE = 1,
	    GAMEPLAYSTATE = 2,
	    GAMEOVERSTATE = 3
        };
	Machine& _arduino;
	Person& _player1;
	Person& _player2;
	int startButtonState;
	int resetButtonState;
	int currentState;
	int buttonPushCounter1;   // counter for the number of button presses
	int buttonPushCounter2;
	int buttonState1;         // current state of the button
	int buttonState2;
	int lastButtonState1;     // previous state of the button
        int lastButtonState2;
        int increment;
public:
/**
 * Constructor which expects an initialized Machine, 2 players, and states. 
 */
	Game(Machine& myArduino, Person& player1, Person& player2, int startButtonState,
	     int resetButtonState, int currentState = STARTSTATE);
/**
 * Plays a pattern on the LED's.
 */
	void led_init();
/**
 * The game resets to base start.
 */
	void reset();
/**
 * Getter for currentState.
 */
	int getCurrentState();
/**
 * Setter for currentState.
 */
	void setCurrentState(int currentState);
/**
 * Setter for the Player biases.
 */
	void setBias(int rate1, int rate2);
/**
 * Updates the state of the Game.
 */
        void updateState();
/**
 * Start state of the Game.
 */
        void start();
/**
 * Play state of the Game.
 */
        void play();
/**
 * "Game Over" state of the Game.
 */
        void gameOver();
/**
 * Checks the Reset Button.
 */
        void checkReset();
/**
 * Getter for lastButton1.
 */
        int getLastButton1();
/**
 * Getter for lastButton2.
 */
        int getLastButton2();
/**
 * Setter for lastButton1.
 */
        void setLastButton1(int state);
/**
 * Setter for lastButton2.
 */
        void setLastButton2(int state);
/**
 * Getter for pushButtonCounter1.
 */
        int getPushButtonCounter1();
/**
 * Getter for pushButtonCounter2.
 */
        int getPushButtonCounter2();
/**
 * Setter for pushButtonCounter1.
 */
        void setPushButtonCounter1(int counter);
/**
 * Setter for pushButtonCounter2.
 */
        void setPushButtonCounter2(int counter);
/**
 * Tests the 2 attached Players.
 */
	void testPlayers();
/**
 * Updates the state of all buttons.
 */
	void updateButtons();
/**
 * Gets the increment.
 */
	int getIncrement();
/**
 * Checks the Start button.
 */
	void checkStart();
/**
 * Prints the states of the entire game.
 */
        void printState();
/**
 * Prints the states of the entire game only if there was a change.
 */
        void printStateDeltas();
};
