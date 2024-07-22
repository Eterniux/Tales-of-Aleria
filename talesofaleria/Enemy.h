#pragma once // Preprocessor directive to ensure header file is included only once
#include "Character.h" // Include the header file for the Character class
#include <vector> // Include the vector library for dynamic arrays

class GameWorld; // Forward declaration of the GameWorld class

class Enemy {
public:
    // Constructor to initialize the Enemy object with coordinates and a reference to the game world
    Enemy(int x, int y, GameWorld& world);

    // Method to move the enemy towards the player
    void moveTowardsPlayer(Character& player);

    // Method to update the position of the enemy in the game world
    void updatePosition(GameWorld& world);

    // Getter method to retrieve the x-coordinate of the enemy
    int getX() const;

    // Getter method to retrieve the y-coordinate of the enemy
    int getY() const;

    // Constructor to initialize the Enemy object with coordinates only
    Enemy(int x, int y);

private:
    bool playerdead = false; // Flag to track if the player is dead
    int x, y; // Coordinates of the enemy
    GameWorld& world; // Reference to the game world where the enemy exists
};
