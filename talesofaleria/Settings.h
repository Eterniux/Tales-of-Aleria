#pragma once // Preprocessor directive to ensure header file is included only once
#include "Character.h" // Including Character header file
#include <iostream> // For input/output operations
#include <string> // For string manipulation
using namespace std;

// Structure to hold keybindings
struct Keybinds {
    char moveUp; // Key for moving up
    char moveDown; // Key for moving down
    char moveLeft; // Key for moving left
    char moveRight; // Key for moving right
};

// Settings class declaration
class Settings {
public:
    // Constructor
    Settings();

    // Display settings menu
    void display() const;

    // Handle user input in settings menu
    int handleInput(); // Return int for user's choice
    int handleInput(bool inGame = false);

    // Set new keybindings
    void setKeybinds(const Keybinds& newKeybinds);

    // Edit keybindings
    void editKeybinds();

    // Load settings from file
    void loadSettings();

    // Display settings
    void display(bool inGame = false) const;

    // Save settings to file
    void saveSettings();

    // Get current keybindings
    Keybinds getKeybinds() const;

private:
    Keybinds keybinds; // Current keybindings
};
