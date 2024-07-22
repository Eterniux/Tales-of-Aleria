#include "Enemy.h" // Include the header file for the Enemy class
#include "GameWorld.h" // Include the header file for the GameWorld class
#include <iostream> // Include the input/output stream library for standard I/O operations
using namespace std; // Use the standard namespace for cout and cin

// Constructor for the Enemy class
Enemy::Enemy(int x, int y, GameWorld& world) : x(x), y(y), world(world) {}


// Method to move the enemy towards the player
void Enemy::moveTowardsPlayer(Character& player) {
    int playerX = player.getX(); // Get the x-coordinate of the player
    int playerY = player.getY(); // Get the y-coordinate of the player
    int dx = playerX - x; // Calculate the horizontal distance between enemy and player
    int dy = playerY - y; // Calculate the vertical distance between enemy and player

    // Move one step towards the player along the longest axis
    if (abs(dx) > abs(dy)) {
        x += (dx > 0 ? 1 : -1); // Increment or decrement x-coordinate based on player position
        if (world.isWall(x, y)) x -= (dx > 0 ? 1 : -1); // Revert if it hits a wall
    }
    else {
        y += (dy > 0 ? 1 : -1); // Increment or decrement y-coordinate based on player position
        if (world.isWall(x, y)) y -= (dy > 0 ? 1 : -1); // Revert if it hits a wall
    }

    // Check if enemy reaches the player
    if (x == playerX && y == playerY) {
        world.playerIsAlive = false; // Set the player's alive status to false
    }
}

// Getter method to retrieve the x-coordinate of the enemy
int Enemy::getX() const {
    return x; // Return the x-coordinate
}

// Getter method to retrieve the y-coordinate of the enemy
int Enemy::getY() const {
    return y; // Return the y-coordinate
}