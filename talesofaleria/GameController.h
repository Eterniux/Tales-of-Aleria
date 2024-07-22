#pragma once // Preprocessor directive to ensure header file is included only once
#include "MainMenu.h" // Include the header file for the MainMenu class
#include "Settings.h" // Include the header file for the Settings class
#include "LoadingScreen.h" // Include the header file for the LoadingScreen class
#include "GameManager.h" // Include the header file for the GameManager class
#include "CharacterCreation.h" // Include the header file for the CharacterCreation class
#include "Character.h" // Include the header file for the Character class
#include "GameWorld.h" // Include the header file for the GameWorld class
#include <string> // For string manipulation

class GameController {
    friend class GameWorld; // Declare GameWorld class as a friend class

public:
    // Enumerate possible game states
    enum GameState {
        MAIN_MENU,
        SETTINGS,
        IN_GAME,
        OUTSIDE,
        IN_SHIP,
        IN_BUILDING,
        WIN,
        ENTRANCE,
        E_EXIT,
        DEAD,
        EXIT
    };

    // Constructor
    GameController();

    // Run the game
    void run();

    // Method to get the name of a game state
    string getStateName(GameState state) {
        switch (state) {
        case MAIN_MENU: return "MAIN_MENU";
        case IN_GAME: return "IN_GAME";
        case OUTSIDE: return "OUTSIDE";
        case IN_SHIP: return "IN_SHIP";
        case ENTRANCE: return "ENTRANCE";
        case IN_BUILDING: return "IN_BUILDING";
        case WIN: return "WIN";
        case E_EXIT: return "E_EXIT";
        case DEAD: return "DEAD";
        case SETTINGS: return "SETTINGS";
        case EXIT: return "EXIT";
        default: return "UNKNOWN STATE";
        }
    }

private:
    // Member variables
    LoadingScreen LoadingScreen; // Object for the loading screen
    GameManager gameManager; // Object for the game manager
    MainMenu mainMenu; // Object for the main menu
    Settings settings; // Object for the settings
    Character character; // Object for the character
    GameWorld gameWorld; // Object for the game world
    GameState currentState; // Current game state
    bool gameIsActive; // Flag indicating if the game is active
    bool inGameSettingsAccessed = false; // Flag indicating if settings were accessed in-game

    // Initialize the game
    void initialize();

    // Main game loop
    void mainLoop();

    // Process input from the main menu
    void processMainMenuInput(int input);

    // Process input from the settings menu
    void processSettingsInput(int input);

    // Display the settings menu
    void displaySettings();

    bool InteriorGenerated; // Flag indicating if interior is generated
};
