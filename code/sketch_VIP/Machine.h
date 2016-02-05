#ifndef VIP_MACHINE_H
#define VIP_MACHINE_H

#include <Servo.h>
/** 
 * This class represents the Machine hardware of the arduino.
 */
class Machine {
	private:
		int LED0;
		int LED1;
		int LED2;
		int LED3;
		int LED4;
		const int startButtonPin; // the Start button pin#
		const int resetButtonPin; // the Reset button pin#
		const int buttonPin1;     // the pin that the first player pushbutton is attached to
		const int buttonPin2;     // the pin that the second player pushbotton is attached to
		const int motor1Control;  // the player 1 motor pin#
		const int motor2Control;  // the player 2 motor pin#
		int armPosition;
	        Servo myservo1; 	  // initialize servo controls
	        Servo myservo2;
                int initializePinCount;
	public:
/**
 * The constructor for the Machine expecting the configuration pins of the hardware.
 */
		Machine(int LED0, int LED1, int LED2, int LED3, int LED4,
			int startButtonPin, int resetButtonPin, int buttonPin1,
			int buttonPin2, int motor1Control, int motor2Control);
/**
 * Setter for any of the attached LED's.
 */
		void setLED(int LEDNumber, bool isOn);
/**
 * Getter for any pin.
 */
                int getPin(int pin);
/**
 * Getter for the resetPin.
 */
                int getResetPin();
 /**
 * Getter for the startPin.
 */
               	int getStartPin();
/**
 * Getter for buttonPin1.
 */
                int getButtonPin1();
/**
 * Getter for buttonPin2.
 */
                int getButtonPin2();
/**
 * Writes to Servo1.
 */
                void writeServo1(int displacement);
/**
 * Writes to Servo2.
 */
                void writeServo2(int displacement);
/**
 * Notifies the Machine of an error, which it will handle.
 * The current implementation uses Serial.
 */
		void error(char* message = "Default Error", int errorCode = 0);a
/**
 * Uses the Machine's serial to print a message.
 */
		void print(char* message);
/**
 * Initializes all attached pins.
 */
                void initializePins();
};
#endif
