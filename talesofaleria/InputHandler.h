#pragma once // Preprocessor directive to ensure header file is included only once
#include "GameWorld.h" // Including GameWorld header file
#include "Character.h" // Including Character header file
#include "Settings.h" // Including Settings header file

// Class for handling user input
class InputHandler {
public:
    // Method to handle user input
    void handleInput(Character& character, GameWorld& gameWorld, const Keybinds& keybinds);
};
