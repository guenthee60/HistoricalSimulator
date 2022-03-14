#ifndef GAME_H
#define GAME_H
#include "country.h"
#include <string.h>
class Game {
	public:
		Country** countryArr;

	
		Game(int); // Initialize a  new game with a given number of countries
		Game(std::string); // Initialize a game from a save
		void doAITurn(int idx);
		void AITurnControlLogic();
		int doTurn();
		void printLeaderboard();
		void saveGame();
		void printToSave();
		~Game();
	private:
		unsigned short int numCountries;
		unsigned int numTurns;
};

#endif

