#include "GameController.h" // Include the header file for the GameController class
#include "InputHandler.h" // Include the header file for the InputHandler class
#include "Character.h" // Include the header file for the Character class
#include "GameWorld.h" // Include the header file for the GameWorld class
#include <cstdlib> // Include the standard library for miscellaneous functions
#include <iostream> // Include the input/output stream library for standard I/O operations
#include <string> // Include the string library for string manipulation
#include <chrono> // Include the chrono library for time-related operations
#include <thread> // Include the thread library for multithreading support
#include <conio.h> // Include the conio library for console input/output operations
using namespace std; // Use the standard namespace for cout and cin

bool completedlevel = false; // Flag to track if a level is completed
bool openSettingsMenu = false; // This global flag controls access to the settings menu

// Constructor for the GameController class
GameController::GameController() : gameWorld(MAP_WIDTH, MAP_HEIGHT), currentState(MAIN_MENU), gameIsActive(false) {
    initialize(); // Call the initialize method to set up the game
}

// Method to initialize the game
void GameController::initialize() {
    LoadingScreen.display(); // Display loading screen at the beginning
}

// Method to start the game
void GameController::run() {
    mainLoop(); // Start the main loop
}

// Main game loop
void GameController::mainLoop() {
    Keybinds currentKeybinds; // Variable to store current keybinds
    InputHandler inputHandler; // Input handler object
    int input = 0; // Variable to store user input

    // Loop until the game state is EXIT
    while (currentState != EXIT) {
        cout << "Current Location: " << getStateName(currentState) << endl; // Display current location
        system("cls"); // Clear the console
        switch (currentState) {
            // Handle main menu state
        case MAIN_MENU:
            mainMenu.display(); // Display the main menu
            input = mainMenu.handleInput(); // Get user input
            processMainMenuInput(input); // Process main menu input
            break;
            // Handle in-game state
        case IN_GAME:
            gameManager.startNewGame(); // New game entry
            gameWorld.generateStartingMap(); // Generate starting map
            character.setPosition(17, 10); // Set character position
            gameWorld.displayUpdateMap(); // Display updated map
            currentState = OUTSIDE; // Move to outside state
            gameWorld.resetMapGeneration(); // Reset map generation
            gameWorld.playerIsAlive = true; // Set player alive
            gameIsActive = true; // Set game active
            break;
            // Handle outside state
        case OUTSIDE:
            currentKeybinds = settings.getKeybinds(); // Get current keybinds
            inputHandler.handleInput(character, gameWorld, currentKeybinds); // Handle input
            gameWorld.setCharacterPosition(character.getX(), character.getY()); // Set character position
            gameWorld.displayUpdateMap(); // Display updated map
            // Check if character reaches entrance or ship
            if (character.getX() == gameWorld.getEntranceX() && character.getY() == gameWorld.getEntranceY()) {
                currentState = ENTRANCE; // Move to entrance state
            }
            if (character.getX() == gameWorld.getshipX() && character.getY() == gameWorld.getshipY()) {
                currentState = IN_SHIP; // Move to in-ship state
            }
            if (openSettingsMenu) {
                currentState = SETTINGS; // Open the settings menu
                openSettingsMenu = false; // Reset the flag
            }
            break;
            // Handle in-ship state
        case IN_SHIP:
            // Check if character is at ship and has items
            if (character.getX() == gameWorld.getshipX() && character.getY() == gameWorld.getshipY()) {
                if (gameWorld.getNumItemsPickedUp() >= 3) {
                    currentState = WIN; // Move to win state
                }
                else {
                    currentState = OUTSIDE; // Move to outside state
                }
            }
            break;
            // Handle entrance state
        case ENTRANCE:
            // Check if interior is generated
            if (gameWorld.interiorGenerated) {
                gameWorld.restoreInteriorMap(); // Restore interior map
                gameWorld.clearEnemies(); // Clear enemies
                gameWorld.generateEnemies(5, character.getX(), character.getY(), 5); // Generate enemies
                character.setPosition(gameWorld.getExitX() + 1, gameWorld.getExitY()); // Set character position
                currentState = IN_BUILDING; // Move to in-building state
            }
            else {
                cout << "================================" << endl;
                cout << "|      Dungeon generated!      |" << endl;
                cout << "================================" << endl;
                system("pause"); // Pause the system
                gameWorld.generateInterior(); // Generate interior
                gameWorld.clearEnemies(); // Clear enemies
                gameWorld.generateEnemies(5, character.getX(), character.getY(), 5); // Generate enemies
                character.setPosition(gameWorld.getExitX() + 1, gameWorld.getExitY()); // Set character position
                currentState = IN_BUILDING; // Move to in-building state
            }
            gameWorld.displayUpdateMap(); // Display updated map
            break;
            // Handle in-building state
        case IN_BUILDING:
            gameWorld.setCharacterPosition(character.getX(), character.getY()); // Set character position
            inputHandler.handleInput(character, gameWorld, currentKeybinds); // Handle input
            gameWorld.moveEnemies(); // Move enemies
            gameWorld.displayUpdateMap(); // Display updated map
            // Check if character reaches exit
            if (character.getX() == gameWorld.getExitX() && character.getY() == gameWorld.getExitY()) {
                currentState = E_EXIT; // Move to exit state
                gameWorld.clearEnemies(); // Clear enemies
            }
            // Check if player is alive
            if (!gameWorld.playerIsAlive) {
                currentState = DEAD; // Move to dead state
            }
            break;
            // Handle win state
        case WIN:
            // Display win message
            cout << "================================" << endl;
            cout << "|         Congratulations!      |" << endl;
            cout << "|            You Won!           |" << endl;
            cout << "================================" << endl;
            system("pause"); // Pause the system
            gameWorld.setNumItemsPickedUp(0); // Reset picked up items
            currentState = MAIN_MENU; // Move to main menu state
            gameIsActive = false; // Set game inactive
            break;
            // Handle exit state
        case E_EXIT:
            currentState = OUTSIDE; // Move to outside state
            gameWorld.restoreStartingMap(); // Restore outside map
            gameWorld.displayUpdateMap(); // Display updated map
            character.setPosition(17, 10); // Set character position
            break;
            // Handle dead state
        case DEAD:
            // Display dead message
            cout << "==============================" << endl;
            cout << "|         You Died!          |" << endl;
            cout << "==============================" << endl;
            system("pause"); // Pause the system
            gameIsActive = false; // Set game inactive
            gameWorld.playerIsAlive = true; // Set player alive
            currentState = MAIN_MENU; // Move to main menu state
            break;
            // Handle settings state
        case SETTINGS:
            displaySettings(); // Display settings
            currentKeybinds = settings.getKeybinds(); // Get current keybinds
            break;
        }
    }
}

// Method to process main menu input
void GameController::processMainMenuInput(int input) {
    char p1 = 'a'; // Temporary variable
    switch (input) {
        // Start a new game
    case 1:
        currentState = IN_GAME; // Move to in-game state
        break;
        // Open settings
    case 2:
        system("cls"); // Clear the console
        currentState = SETTINGS; // Move to settings state
        break;
        // Algorithm Showcase
    case 3:
        system("cls"); // Clear the console
        while (p1 != 'Q' && p1 != 'q') {
            gameWorld.resetMapGeneration(); // Reset map generation
            gameWorld.restoreInteriorMap(); // Restore interior map
            gameWorld.generateInterior(); // Generate interior
            gameWorld.displayUpdateMap(); // Display updated map
            cout << "\033[1;37m\033[1;31mPress any key to regenerate map. \033[0m Q to exit" << endl; // Display message
            p1 = _getch(); // Get user input
        }
        break;
        // Exit
    case 4:
        currentState = EXIT; // Move to exit state
        break;
        // Invalid input
    default:
        std::cout << "Invalid choice. Please select a valid option.\n"; // Display message
        break;
    }
}

// Method to process settings input
void GameController::processSettingsInput(int input) {
    if (gameIsActive) { // Check if the game is active
        switch (input) {
            // Resume game
        case 1:
            currentState = OUTSIDE; // Move to in-game state
            break;
            // Change keybinds
        case 2:
            settings.editKeybinds(); // Edit keybinds
            break;
            // Go to main menu
        case 3:
            currentState = MAIN_MENU; // Move to main menu state
            gameIsActive = false; // Set game inactive
            break;
            // Exit
        case 4:
            currentState = EXIT; // Move to exit state
            break;
            // Invalid input
        default:
            cout << "Invalid choice. Please select a valid option." << endl; // Display message
            system("pause"); // Pause the system
            break;
        }
    }
    else { // Game is not active
        switch (input) {
            // Change keybinds
        case 1:
            settings.editKeybinds(); // Edit keybinds
            break;
            // Go to main menu
        case 2:
            currentState = MAIN_MENU; // Move to main menu state
            break;
            // Exit
        case 3:
            currentState = EXIT; // Move to exit state
            break;
            // Invalid input
        default:
            cout << "Invalid choice. Please select a valid option." << endl; // Display message
            system("pause"); // Pause the system
            break;
        }
    }
}

// Method to display settings
void GameController::displaySettings() {
    int input; // Variable to store user input
    do {
        system("cls"); // Clear the console
        settings.display(gameIsActive); // Display settings based on game state
        cout << "Enter your choice: ";
        cin >> input; // Get user input
        processSettingsInput(input); // Process settings input
    } while (currentState == SETTINGS); // Continue displaying settings until user exits
}