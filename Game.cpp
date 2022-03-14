// A demonstration of my C++
#include <iostream>
#include <thread>
#include <string>
#include <stdio.h>
#include <stdlib.h>

// Written headers
#include "country.h"
#include "game.h"



bool getResponse();
int setNumCountries();




// initializes the countries/players and sets up the game.
// runs the overall logic for the turns. Turn-specific code
// is found in the doTurn and doAITurn function
int main()
{

    Game* gme = NULL;
    int numCountries;
    int numResponse = 0;
    bool ynResponse = false;
    

    std::cout << "Welcome to the Game\n";
    std::cout << "Please select an option: \n";
    std::cout << "1: Start a New Game\n";
    std::cout << "2: Load a Saved Game\n";

    do {
        std::cin >> numResponse;
    } while (numResponse != 1 && numResponse != 2);

    

    // Load a saved game
    if (numResponse == 2) {
        std::string fileName;
        std::cout << "Please enter the name of a save file: \n";
        std::cin >> fileName;
        // Use the constructor that takes a string to instatiate
        // a game with save data
        // Use static so savedGame isn't lost when leaving scope
        static Game savedGame(fileName);
        gme = &savedGame;
    }
 

    // Start a new game
    if (numResponse == 1) {

        // Set the number of players
        do {
            numCountries = setNumCountries();
            std::cout << numCountries << " will play. Okay? (Y/N)\n";
            ynResponse = getResponse();
        } while (ynResponse == false);

        // Instantiate the game object
        // Use static so the game object isn't lost when leaving scope
        static Game newGame(numCountries);
        gme = &newGame;
    }

    
    // Do the turns
    do {
        numResponse = gme->doTurn();
        if (numResponse != 6) // don't do the AI turns if the player quits
            gme->AITurnControlLogic();
    } while (numResponse != 6); // end the loop when the player quits

    return 0;
}





int setNumCountries() {
    int a = -1;
    std::cout << "How many countries should play?\n";
    while (a < 0 || a > 16) {
        std::cin >> a;
        if (a < 0 || a > 16)
            std::cout << "Please enter a positive integer between 2 and 16.\n";
    }

    return a;
}

// Handle simple yes-no responses here to clear up main()
bool getResponse() {
    char response;
    std::cin >> response;

    if (response == 'y' || response == 'Y')
        return true;
    else
        return false;
}


