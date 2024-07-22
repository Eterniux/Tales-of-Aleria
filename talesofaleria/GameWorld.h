#pragma once // Preprocessor directive to ensure header file is included only once
#include <vector> // For using vector containers
#include <string> // For using string class
#include "Character.h" // For including Character class
#include "Enemy.h" // For including Enemy class
#include "chrono" // For time-related functionality
#include <thread> // For multi-threading support
#include <iostream> // For input/output operations
using namespace std;

const int MAP_WIDTH = 40; // Width of the game map
const int MAP_HEIGHT = 21; // Height of the game map
const char WALL = (char)176; // Character representing a wall
const char EMPTY = ' '; // Character representing an empty space

// Structure representing a room in the game world
struct Room {
    int x, y; // Top-left corner coordinates
    int width, height; // Dimensions of the room

    Room(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    // Method to check if this room overlaps with another room
    bool overlaps(const Room& other) const {
        return x < other.x + other.width && x + width > other.x &&
            y < other.y + other.height && y + height > other.y;
    }
};

// Class representing the game world
class GameWorld {
    friend class GameController;
public:
    // Constructor with width and height parameters
    GameWorld(int width, int height);

    // Methods for map generation and manipulation
    void backupStartingMap(); // Backup the starting map
    void backupInteriorMap(); // Backup the interior map
    void restoreStartingMap(); // Restore the starting map
    void restoreInteriorMap(); // Restore the interior map
    void generateStartingMap(); // Generate the starting map
    void generateInterior(); // Generate the interior
    void resetMapGeneration(); // Reset map generation flags

    void displayUpdateMap() const; // Method to display and update the game map

    void setCharacterPosition(int x, int y); // Method to set the position of the character
    void setCharacter(const Character& character); // Method to set the character object
    void updateCharacterPosition(char input); // Method to update the character position based on user input

    bool isWall(int x, int y) const; // Method to check if there is a wall for collision

    bool ifplaced = false; // Flag for character placement
    bool playerIsAlive = true; // Flag for player status

    Character getCharacter() const { return character; } // Getter for character object

    // Getters and setters for entrance, exit, and ship coordinates
    void setEntranceX(int x) { entranceX = x; }
    void setEntranceY(int y) { entranceY = y; }
    void setExitX(int x) { exitX = x; }
    void setExitY(int y) { exitY = y; }
    int getEntranceX() const { return entranceX; }
    int getEntranceY() const { return entranceY; }
    int getExitX() const { return exitX; }
    int getExitY() const { return exitY; }
    void setshipX(int x) { shipX = x; }
    void setshipY(int y) { shipY = y; }
    int getshipX() const { return shipX; }
    int getshipY() const { return shipY; }

    // Method to check if an item can be picked up at the given position
    bool pickUpItem(int x, int y);

    // Getters and setters for the number of items picked up
    int getNumItemsPickedUp() const { return numItemsPickedUp; }
    void setNumItemsPickedUp(int numItems) { numItemsPickedUp = numItems; }

    // Methods for enemy generation and movement
    void generateEnemies(int numEnemies, int bufferX, int bufferY, int safeZoneRadius);
    void moveEnemies(); // Move enemies
    void clearEnemies(); // Clear enemies from the map

    // Getters and setters for the game map and interior map data
    const vector<vector<char>>& getMap() const { return map; }
    void setMap(const vector<vector<char>>& newMap) { map = newMap; }
    const vector<vector<char>>& getInteriorMapData() const { return interiorMapData; }
    void setInteriorMapData(const vector<vector<char>>& newMap) { interiorMapData = newMap; }

private:
    chrono::steady_clock::time_point lastEnemyMoveTime; // Time point for last enemy movement
    std::chrono::milliseconds enemyMoveDelay{ 500 }; // Delay for enemy movement

    int numItemsPickedUp; // Number of items picked up

    int shipX, shipY; // Ship coordinates
    int entranceX, entranceY; // Entrance coordinates
    int exitX, exitY; // Exit coordinates

    int width; // Width of the game world
    int height; // Height of the game world

    vector<vector<char>> map; // 2D vector to store the game world map
    vector<vector<char>> startingMapData; // Data for the starting map
    vector<vector<char>> interiorMapData; // Data for the interior map

    vector<Room> rooms; // Vector to store the rooms in the interior world
    Character character; // Character object
    vector<Enemy> enemies; // Vector to store enemies

    bool mapGenerated; // Flag for map generation
    bool interiorGenerated; // Flag for interior generation
};
