#ifndef COUNTRY_H
#define COUNTRY_H
#include <iostream>
#include <time.h>
#include <random>

class Country {
	private: 
		int idx; // track the index of the country, used to place it on the map
		int money; // accumulated money to build a factory or army
		int factories;
		int military;
		
	public: 
		bool turnDone;
		Country();
		Country(int);
		Country(int, int);
		void endTurn();
		int getIdx();
		int getMoney();
		int getFactories();
		int getMilitary();
		void addFactory();
		void addFactory(int);
		void addMilitary();
		void addMilitary(int);
		void addMoney(int);

};

#endif