#include <iostream>
#include <string>
#include <fstream>
#include "game.h"

// Set up a game with a given number of countries
Game::Game(int countryCount) {
	// Create a new country pointer so countryArr can be dereferenced with []
	countryArr = new Country*;
	numCountries = countryCount;
	numTurns = 0;
	std::cout << "Attempting to allocate countryArr\n";
	for (int i = 0; i < countryCount; i++) {
		countryArr[i] = new Country(i);
	}
	std::cout << "Allocated countryArr\n";
}


// Start a game from a save file
Game::Game(std::string fileName) {
	std::ifstream saveFile;

	// Check whether the user supplied the .gameSave extension
	std::size_t found = fileName.find(".gameSave");

	// if it did not have the extension
	if (found == std::string::npos)
		fileName.append(".gameSave"); // add the extension

	// else it did have the extension
	std::cout << "Attempting to open save file " << fileName << "\n";
	numTurns = 0;
	saveFile.open(fileName);

	if (saveFile.is_open()) {
		std::string line;
		countryArr = new Country*;

		std::getline(saveFile, line);

		numCountries = std::stoi(line);

		for (int j = 0; j < numCountries; j++) {
			countryArr[j] = new Country(j, j); // pass two ints so we're starting with zeroed values using the third constructor
		}
		std::cout << "Allocated countries from save\n";
		for (int i = 0; i < numCountries; i++) {
			std::getline(saveFile, line);
			countryArr[i]->addMilitary(std::stoi(line));
			std::getline(saveFile, line);
			countryArr[i]->addFactory(std::stoi(line));
			std::getline(saveFile, line);
			countryArr[i]->addMoney(std::stoi(line));
			std::cout << "Successfully loaded country " << i << "\n";
		}

		std::cout << "Loading complete\n";

	}

	else {
		std::cout << "Error: cannot open save file " << fileName << "\n";
		Game::~Game(); // deallocate memory
		exit(0);
	}
}


// Write the stats of each country to a .gameSave file
// Currently does not check if the file already exists
// Changes stdout to the save file and then prints to it
void Game::saveGame() {
	std::ofstream saveFile;
	std::string saveFileName;
	std::cout << "Please enter a name for the save file: \n";
	std::cin >> saveFileName;

	saveFileName.append(".gameSave");

	saveFile.open(saveFileName);

	if (saveFile.is_open()) {
		
		// Change stdout from here:
		// https://stackoverflow.com/questions/10150468/how-to-redirect-cin-and-cout-to-files
		std::streambuf* coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(saveFile.rdbuf()); // change the output to the save file
		printToSave();

		std::cout.rdbuf(coutbuf); // reset standard to output

		saveFile.close();
	}
	else
		std::cout << "Error opening the save file.\n";
}


// Make the AI countries do their turns, skipping
// index 0 because that's the human player
void Game::AITurnControlLogic() {
	// skip idx 0 because that's the human player
	for (int i = 1; i < numCountries; i++) {
		doAITurn(i);
		std::cout << "Completed Country " << i << "'s turn.\n";
	}
}

// The AI's turn. Currently just selects an option at random.
// Might declare war if a neighbor has a smaller army
void Game::doAITurn(int idx) {
	int choice = rand() % 50 + 1;

	// 20% chance to build a factory if enough money
	if (choice < 10 && countryArr[idx]->getMoney() > 9)
		countryArr[idx]->addFactory();

	// 20% chance to build an army
	else if (choice >= 10 && choice < 20 && countryArr[idx]->getMoney() > 9)
		countryArr[idx]->addMilitary();

	// 60% chance to do nothing/save money
	else
		countryArr[idx]->endTurn();

}


// Do the player's turn
int Game::doTurn() {
	Country* c = countryArr[0];
	int response;
	do {
		c->turnDone = false;
		std::cout << "What would you like to do?\n";
		std::cout << "1: View stats 2: Build an Army (ends turn) 3: Build a Factory (ends turn) 4: Nothing 5: View Leaderboard 6: Save Game 7: Quit Game\n";
		std::cin >> response;

		switch (response) {
		case (1):
			std::cout << "Money: " << c->getMoney() << "\n";
			std::cout << "Armies: " << c->getMilitary() << "\n";
			std::cout << "Factories: " << c->getFactories() << "\n";
			break;
		case(2):
			c->addMilitary();
			break;
		case(3):
			c->addFactory();
			break;
		case(4):
			c->endTurn();
			break;
		case(5):
			printLeaderboard();
			break;
		case(6):
			saveGame();
			break;
		case(7):
			return 6;
			break;
		}
	} while (c->turnDone == false);
}


// Print the statistics of all countries
void Game::printLeaderboard() {
	for (int i = 0; i < numCountries; i++) {
		std::cout << "Country " << countryArr[i]->getIdx() << "\n";
		std::cout << "Military: " << countryArr[i]->getMilitary() << "\n";
		std::cout << "Factories: " << countryArr[i]->getFactories() << "\n";
		std::cout << "Money: " << countryArr[i]->getMoney() << "\n";
		std::cout << "--------------------\n";
	}
}


// Essentially a lighter version of the printLeaderboard
// Lighter so it's easier to read in when loading a save game
void Game::printToSave() {
	// print the number of countries
	std::cout << numCountries << "\n";
	for (int i = 0; i < numCountries; i++) {
		std::cout << countryArr[i]->getMilitary() << "\n";
		std::cout << countryArr[i]->getFactories() << "\n";
		std::cout << countryArr[i]->getMoney() << "\n";
	}
}



// The destructor (delete the dynamically allocated memory)
Game::~Game() {
	delete[] countryArr;
}