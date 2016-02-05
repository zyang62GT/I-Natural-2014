#pragma once
/** 
 * This class represents the players involved in the game.
 */
class Person {
	private:
		int bias;
		int score;
	public:
/**
 * Default Constructor for the Person.
 */
		Person();
/**
 * Constructor with bias setter.
 */
		explicit Person(int bias);
/**
 * Getter for score.
 */
		const int getScore();
/**
 * Getter for the bias.
 */
		const int getBias();
/**
 * Setter for the bias. Used in case of default constructor or if bias
 * is recalculated.
 */
		void setBias(int bias);
};
