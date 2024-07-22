#include "InputHandler.h" // Including InputHandler header file
#include "Character.h" // Including Character header file
#include "Settings.h"  // Including Settings header file
#include "GameWorld.h" // Including GameWorld header file
#include "GameController.h" // Including GameController header file
#include <iostream> // For input/output operations
#include <conio.h> // For console input/output operations

extern Settings settings; // External declaration for the settings object
extern bool openSettingsMenu; // External declaration for the settings menu flag

// Function to handle user input
void InputHandler::handleInput(Character& character, GameWorld& gameWorld, const Keybinds& keybinds) {
    if (_kbhit()) { // Check if a key has been pressed
        char input = _getch(); // Get the character input from the keyboard

        Keybinds currentKeybinds = settings.getKeybinds(); // Get the current keybinds from the settings

        // Handle character movement based on input
        if (input == currentKeybinds.moveUp) // Move character up
            character.moveUp(gameWorld);
        else if (input == currentKeybinds.moveDown) // Move character down
            character.moveDown(gameWorld);
        else if (input == currentKeybinds.moveLeft) // Move character left
            character.moveLeft(gameWorld);
        else if (input == currentKeybinds.moveRight) // Move character right
            character.moveRight(gameWorld);
        else if (input == 'f' || input == 'F') { // Pick up item
            if (gameWorld.pickUpItem(character.getX(), character.getY())) {
                // Item picked up successfully
                std::cout << "Picked up an item! Total items picked up: " << gameWorld.getNumItemsPickedUp() << std::endl;

            }
            else {
                // No item at the current position
                std::cout << "No item to pick up at this position." << std::endl;
            }
        }
        else if (input == 'e' || input == 'E') { // Open settings menu
            openSettingsMenu = true; // Set the flag to open the settings menu
        }
    }
}
