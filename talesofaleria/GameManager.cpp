#include "GameManager.h" // Include the header file for the GameManager class
#include <fstream> // Include the file stream library for file I/O operations
#include <iostream> // Include the input/output stream library for standard I/O operations
#include <chrono> // Include the chrono library for time-related operations
#include <thread> // Include the thread library for multithreading support
using namespace std; // Use the standard namespace for cout and cin

// Constructor for GameManager class
GameManager::GameManager() : gameWorld(MAP_HEIGHT, MAP_WIDTH) {
}

// Method to start a new game
void GameManager::startNewGame() {
    // Get the instance of CharacterCreation
    CharacterCreation& characterCreation = CharacterCreation::getInstance();

    // Start the character creation process
    characterCreation.startCharacterCreation();

    // Create the player character
    Character playerCharacter = characterCreation.createCharacter();

    // Set the character in the game world
    gameWorld.setCharacter(playerCharacter);
}
