#include "Game.h"
#include <Arduino.h>
Game::Game(Machine& myArduino, Person& player1, Person& player2, int startButtonState, int resetButtonState, int currentState) :  _arduino(myArduino), _player1(player1), _player2(player2) {
    this->startButtonState = startButtonState;
    this->resetButtonState = resetButtonState;
    this->currentState = currentState;
    buttonPushCounter1 = 0;   
    buttonPushCounter2 = 0;
    buttonState1 = 0;         
    buttonState2 = 0;
    lastButtonState1 = 0;    
    lastButtonState2 = 0;
}
void Game::updateButtons() {
    lastButtonState1 = buttonState1;
    lastButtonState2 = buttonState2;
    buttonState1 = _arduino.getButtonPin1();
    buttonState2 = _arduino.getButtonPin2();
    resetButtonState = _arduino.getResetPin();
    startButtonState = _arduino.getStartPin();
}
void Game::updateState() {
  	updateButtons();
	checkStart();
  	checkReset();
  	switch(getCurrentState()) {
    	case INITIALSTATE:
       		   	reset();
          		break;
    	case STARTSTATE:
          		start();
          		break;
    	case GAMEPLAYSTATE:
          		play();
          		break;
    	case GAMEOVERSTATE:
          		gameOver();
          		break;
    	default:
	 		_arduino.error("Unknown State");
	  		break;
  	}
}
void Game::testPlayers() {
	_arduino.print("Testing Players");
	for(int i=0 ; i<10000 ; i++) {
      		updateButtons();	
		if (buttonState1 != lastButtonState1 && buttonState1 == HIGH) {
          		buttonPushCounter1++;
     		 }
     		if (buttonState2 != lastButtonState2 && buttonState2 == HIGH) {
          		buttonPushCounter2++;
      		}
	}
      	delay(1);
}
void Game::start() {
	_arduino.print("Start State");
      	for (int i = 0; i < 5; i++) {
       		 _arduino.setLED(i, true);
      	}
      	led_init();
      	delay(100);
      	currentState = GAMEPLAYSTATE;
}
void Game::reset() {
	_arduino.print("Reset");
 	buttonPushCounter1 = 0;   
    	buttonPushCounter2 = 0;
    	buttonState1 = 0;         
    	buttonState2 = 0;
    	lastButtonState1 = -1;    
    	lastButtonState2 = -1;
}
void Game::play() {
	int increment = getIncrement();
      	_arduino.writeServo1(int(32.5+increment));
      	_arduino.writeServo2(75-int(32.5+increment));
    	if (int(32.5)+increment>=75){
      	// player 1 win
      		currentState = GAMEOVERSTATE;
    	} else if (int(32.5+increment)<=0){
      	// player 2 win
      		currentState = GAMEOVERSTATE;
    	} 
}
void Game::gameOver() {
    	updateButtons();
    	checkReset();
}
void Game::led_init() {
    	for (int counterStart = 0; counterStart < 5; counterStart++) {
        	_arduino.setLED(counterStart, false);
    	}
}
int Game::getIncrement() {
	int increment;
	for(increment = 0 ; abs(increment)<33 ; ) {
		updateButtons(); 
      		if (buttonState1 != lastButtonState1 && buttonState1 == HIGH) {
          		increment += _player1.getBias();
        	}
      		if (buttonState2 != lastButtonState2 && buttonState2 == HIGH) {
          		increment += -1 * _player2.getBias();
        	}
   	}
	return increment;
}
void Game::checkStart() {
	if (startButtonState == HIGH && currentState == INITIALSTATE) {
		currentState = STARTSTATE;
  	}
}
void Game::checkReset() {
	if(resetButtonState == HIGH) {
		for (int i = 0; i < 5; i++) {
			_arduino.setLED(i, true);
	  	} 
      		led_init();
      		currentState = INITIALSTATE;
    	} 
}

void Game::setBias(int rate1, int rate2) {
    int bias1 = rate2 / rate1;
    int bias2 = rate1 / rate2;
    _player1.setBias(bias1);
    _player2.setBias(bias2);
}
int Game::getCurrentState() { const
    return currentState;
}
void Game::setCurrentState(int currentState) {
    this->currentState = currentState;
}
int Game::getLastButton1() {
  return  lastButtonState1;
}
int Game::getLastButton2() {
  return  lastButtonState2;
}
void Game::setLastButton1(int state) {
  lastButtonState1 = state;
}
void Game::setLastButton2(int state) {
  lastButtonState2 = state;
}
int Game::getPushButtonCounter1() {
  return  buttonPushCounter1;
}
int Game::getPushButtonCounter2() {
  return  buttonPushCounter2;
}
void Game::setPushButtonCounter1(int count) {
  buttonPushCounter1 = count;
}
void Game::setPushButtonCounter2(int count) {
  buttonPushCounter2 = count;
}
