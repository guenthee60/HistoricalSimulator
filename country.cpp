#include <iostream>
#include "country.h"

// end this player's turn (after building a factory or army)
void Country::endTurn() {
	money += factories; // gain 1 money for each factory
	turnDone = true;
}


int Country::getIdx() {
	return idx;
}

// Add a variable amount of money (typically based on number of factories)
void Country::addMoney(int a) {
	money += a;
}

int Country::getMoney() {
	return money;
}

int Country::getFactories() {
	return factories;
}

int Country::getMilitary() {
	return military;
}

// build a factory
void Country::addFactory() {
	if (money > 9) {
		factories++;
		money -= 10;
		endTurn();
	}

	else
		std::cout << "Not enough money to build a factory.\n";
}

// Overload of add factories, for load from a save
void Country::addFactory(int a) {
	factories += a;
}

// build an army
void Country::addMilitary() {
	if (money > 9) {
		military++;
		money -= 10;
		endTurn();
	}

	else
		std::cout << "Not enough money to build an army.\n";
}


// Overload of addMilitary, for load from a save
void Country::addMilitary(int a) {
	military += a;
}

// default constructor
Country::Country() {
	idx = rand() % 100 + 1;
	money = 10;
	factories = 1;
	military = 1;
	turnDone = false;
}

// secondary constructor
// pass an int as the country's index
Country::Country(int i) {
	idx = i;
	money = 10;
	factories = 1;
	military = 1;
	turnDone = false;
}

// pass two ints for loading a country's data from a save file
Country::Country(int i, int j) {
	idx = i;
	money = 0;
	factories = 0;
	military = 0;
	turnDone = false;
}