#pragma once // Preprocessor directive to ensure header file is included only once
#include <string> // For string manipulation
using namespace std;

class GameWorld;

class Character {
public:
    // Constructors
    Character() : name(""), characterClass(""), x(1), y(1), worldWidth(40), worldHeight(21) {} // Default constructor with initialization
    Character(const string& name, const string& characterClass); // Parameterized constructor

    // Getters and setters for character position
    int getX() const; // Get the character's x-coordinate
    int getY() const; // Get the character's y-coordinate
    void setPosition(int x, int y); // Set the character's position

    // Movement methods
    void moveUp(GameWorld& world);
    void moveDown(GameWorld& world);
    void moveLeft(GameWorld& world);
    void moveRight(GameWorld& world);

    // Getters for name and character class
    string getName() const { return name; } // Get the character's name
    string getCharacterClass() const { return characterClass; } // Get the character's class

private:
    // Member variables
    string name; // Character's name
    string characterClass; // Character's class
    int x; // Character's x-coordinate
    int y; // Character's y-coordinate


    int worldWidth; // Character's world width border
    int worldHeight; // Character's world height border
};
