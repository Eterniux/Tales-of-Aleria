#pragma once // Preprocessor directive to ensure header file is included only once
#include <iostream> // For input/output operations
#include <string> // For string manipulation
#include "Character.h" // Include the Character class
using namespace std;

class CharacterCreation {
public:
    // Delete the copy constructor and copy assignment operator
    CharacterCreation(const CharacterCreation&) = delete;
    void operator=(const CharacterCreation&) = delete;

    // Singleton design pattern - get the instance of CharacterCreation
    static CharacterCreation& getInstance() {
        static CharacterCreation instance;
        return instance;
    }

   
    void startCharacterCreation(); // Method to start the character creation process
    Character createCharacter(); // Method to create the character
    const string& getCharacterName() const { return characterName; } // Getter for the character's name
    const string& getChosenClass() const { return chosenClass; } // Getter for the chosen character class

private:
    // Private constructor to prevent instantiation
    CharacterCreation() {}

    // Private member variables
    string characterName; // Name of the character being created
    string chosenClass; // Chosen class for the character

    // Private member functions
    void chooseCharacterName(); // Method to choose the character's name
    void chooseCharacterClass(); // Method to choose the character's class
    bool displayCharacterSummary(); // Method to display the character summary
};
