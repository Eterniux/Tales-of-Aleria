#pragma once // Preprocessor directive to ensure header file is included only once
#include "CharacterCreation.h" // Include the header file for the CharacterCreation class
#include "GameWorld.h" // Include the header file for the GameWorld class

// GameManager class responsible for managing game initialization and loading
class GameManager {
public:
    // Constructor for GameManager class
    GameManager();

    // Method to start a new game
    void startNewGame();

private:
    GameWorld gameWorld; // Instance of GameWorld for managing the game environment
};
