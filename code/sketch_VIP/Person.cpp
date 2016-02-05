#include "Person.h"
Person::Person() {
	this->bias = 0;
	this->score = 0;
}
Person::Person(int bias) {
	this->bias = bias;
	this->score = 0;
}
const int Person::getScore() {
	return this->score;
}
const int Person::getBias() {
	return this->bias;
}
void Person::setBias(int bias) {
	this->bias = bias;
}