#include <Servo.h>
#include <Arduino.h>
#include "Machine.h"
Machine::Machine(int LED0, int LED1, int LED2, int LED3, int LED4, int startButtonPin, int resetButtonPin,
				 int buttonPin1, int buttonPin2, int motor1Control, int motor2Control) : startButtonPin(startButtonPin),
				 resetButtonPin(resetButtonPin), buttonPin1(buttonPin1), buttonPin2(buttonPin2), motor1Control(motor1Control),
				 motor2Control(motor2Control), myservo1(), myservo2() {
	this->LED0 = LED0;
	this->LED1 = LED1;
	this->LED2 = LED2;
	this->LED3 = LED3;
	this->LED4 = LED4;
	armPosition = 0;
        initializePinCount = 0;
}
void Machine::initializePins() {
        if (initializePinCount == 0) {
            // initialize the digital pin as an output:
	    pinMode(LED0, OUTPUT);
	    pinMode(LED1, OUTPUT);  
	    pinMode(LED2, OUTPUT);  
	    pinMode(LED3, OUTPUT);  
	    pinMode(LED4, OUTPUT);  
	    // initialize the button pins as inputs:
	    pinMode(buttonPin1, INPUT);
	    pinMode(buttonPin2, INPUT); 
	    pinMode(startButtonPin, INPUT);  
	    pinMode(resetButtonPin, INPUT);
	    myservo1.attach(motor1Control);
	    myservo2.attach(motor2Control);
	    // initialize serial communication:
	    Serial.begin(9600);
            initializePinCount++;
        }
}
void Machine::setLED(int LEDNumber, bool isOn) {
	int _led;
	switch (LEDNumber) {
	case 0:
		_led = LED0;
		break;
	case 1:
		_led = LED1;
		break;
	case 2:
		_led = LED2;
		break;
	case 3:
		_led = LED3;
		break;
	case 4:
		_led = LED4;
		break;
	default:
                
		break;
	}
	if (isOn) {
		digitalWrite(_led, HIGH);
	} else {
		digitalWrite(_led, LOW);
	}
}
void Machine::print(char* message) {
	Serial.print(message);
}
int Machine::getPin(int pin) {
	return digitalRead(pin) ;
}
int Machine::getResetPin() {
	return getPin(resetButtonPin);
}
int Machine::getStartPin() {
	return getPin(startButtonPin); 
}
int Machine::getButtonPin1() {
	return getPin(buttonPin1); 
}
int Machine::getButtonPin2() {
	return getPin(buttonPin2); 
}
void Machine::writeServo1(int displacement) {
	myservo1.write(displacement);
}
void Machine::writeServo2(int displacement) {
	myservo2.write(displacement);
}
void Machine::error(char* message, int errorCode) {
	print("ERROR: ");
	print(message);  
}



