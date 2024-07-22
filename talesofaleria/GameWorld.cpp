#include "GameWorld.h" // Include the header file for the GameWorld class
#include "Enemy.h" // Include the header file for the Enemy class
#include <iostream> // Include the input/output stream library for standard I/O operations
#include <cstdlib> // Include the C standard library for general utilities
#include <ctime> // Include the C standard library for time functions
#include <vector> // Include the vector library for dynamic arrays
#include <chrono> // Include the chrono library for time-related operations
#include <thread> // Include the thread library for multithreading support
using namespace std; // Use the standard namespace for cout and cin

// Constructor with width and height parameters
GameWorld::GameWorld(int width, int height) : width(MAP_WIDTH), height(MAP_HEIGHT) {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator with the current time
    lastEnemyMoveTime = std::chrono::steady_clock::now(); // Initialize the last enemy move time
    generateStartingMap(); // Generate the starting map
    interiorGenerated = false; // Set interiorGenerated flag to false initially
}

// Method to generate the starting map
void GameWorld::generateStartingMap() {
    if (!mapGenerated) { // Check if the map is not already generated
        enemies.clear(); // Clear the enemies vector
        // Initialize the map with ' ' representing the deserted outside
        map = vector<vector<char>>(MAP_HEIGHT, vector<char>(MAP_WIDTH, ' '));

        // Place the player's ship
        int shipX = 5, shipY = 5; // Example coordinates for the ship
        setshipX(shipX); // Set the ship X-coordinate
        setshipY(shipY); // Set the ship Y-coordinate
        for (int y = shipY; y < shipY + 2; ++y) {
            for (int x = shipX; x < shipX + 3; ++x) {
                map[y][x] = static_cast<char>(254); // Ship representation
            }
        }

        // Define the building dimensions and location
        int buildingTopLeftX = MAP_WIDTH - 20; // X-coordinate of the building's top left corner
        int buildingTopLeftY = (MAP_HEIGHT - 15) / 2; // Center the building vertically
        int buildingWidth = 20; // Building width
        int buildingHeight = 15; // Building height, adjusted to fit within the map height

        // Create the building structure
        for (int y = buildingTopLeftY; y < buildingTopLeftY + buildingHeight; ++y) {
            for (int x = buildingTopLeftX; x < buildingTopLeftX + buildingWidth; ++x) {
                // Outline with walls, except for the entrance
                bool isHorizontalWall = y == buildingTopLeftY || y == buildingTopLeftY + buildingHeight - 1;
                bool isVerticalWall = x == buildingTopLeftX || x == buildingTopLeftX + buildingWidth - 1;
                if (isHorizontalWall || isVerticalWall) {
                    map[y][x] = static_cast<char>(176);
                }
            }
        }

        // Mark the entrance to the building in the middle of the vertical wall
        int entranceX = 20; // X-coordinate of the vertical wall
        int entranceY = 10; // Y-coordinate in the middle of the wall
        setEntranceX(entranceX); // Set entrance X-coordinate
        setEntranceY(entranceY); // Set entrance Y-coordinate
        map[entranceY][entranceX] = (char)219; // Clear the entrance

        mapGenerated = true; // Set mapGenerated flag to true
        backupStartingMap(); // Backup the starting map
    }
}

// Method to generate the interior of the building
void GameWorld::generateInterior() {
    if (!interiorGenerated) { // Check if the interior is not already generated
        // Clear the map except for the building outline
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                map[y][x] = WALL; // Set all cells to walls
            }
        }
        // Place a permanent square room on the left middle part of the map
        int roomWidth = 10; // Width of the room
        int roomHeight = 10; // Height of the room
        int roomX = 1; // X-coordinate to ensure it's on the left side
        int roomY = (MAP_HEIGHT - roomHeight) / 2; // Y-coordinate to center it vertically

        Room permanentRoom(roomX, roomY, roomWidth, roomHeight); // Create a permanent room object

        // Fill in room area
        for (int y = roomY; y < roomY + roomHeight; ++y) {
            for (int x = roomX; x < roomX + roomWidth; ++x) {
                map[y][x] = EMPTY; // Set cells in the room area to empty
            }
        }

        // Place the exit on the left middle of the permanent room
        int exitX = roomX; // Exit on the left side of the room
        int exitY = roomY + roomHeight / 2; // Exit in the middle vertically
        setExitX(exitX); // Set exit X-coordinate
        setExitY(exitY); // Set exit Y-coordinate
        map[exitY][exitX] = (char)219; // Mark the exit

        rooms.clear(); // Reset the vector of rooms stored from previous runs
        // Randomly generate additional rooms inside the building
        int maxRooms = 9; // Adjust to allow for the permanent room
        int attempt = 0;
        bool exitPlaced = true; // Set to true since the exit is already placed
        while (rooms.size() < maxRooms && attempt < 100) {
            int newRoomWidth = rand() % 8 + 3; // Room width between 3 and 10
            int newRoomHeight = rand() % 8 + 3; // Room height between 3 and 10
            int newRoomX = rand() % (MAP_WIDTH - newRoomWidth - 3) + 2;
            int newRoomY = rand() % (MAP_HEIGHT - newRoomHeight - 3) + 2;

            Room newRoom(newRoomX, newRoomY, newRoomWidth, newRoomHeight); // Create a new room object

            bool overlap = false;
            for (const Room& room : rooms) {
                if (newRoom.overlaps(room)) {
                    overlap = true;
                    break;
                }
            }

            if (!overlap) {
                rooms.push_back(newRoom); // Add new room to list
                // Fill in new room area
                for (int y = newRoomY; y < newRoomY + newRoomHeight; ++y) {
                    for (int x = newRoomX; x < newRoomX + newRoomWidth; ++x) {
                        map[y][x] = EMPTY; // Set cells in the new room area to empty
                    }
                }
            }
            ++attempt;
        }

        // Place items on the ground
        int numItems = rand() % 7 + 5; // Generate between 5 to 11 items
        vector<pair<int, int>> placedItems; // Store placed item coordinates

        for (int i = 0; i < numItems; ++i) {
            bool itemPlaced = false;
            int attempts = 0;
            while (!itemPlaced && attempts < 50) { // Limit attempts to avoid infinite loops
                int itemX = rand() % (MAP_WIDTH - 2) + 1;
                int itemY = rand() % (MAP_HEIGHT - 2) + 1;

                // Check if the selected position is not a wall and not already used
                if (!isWall(itemX, itemY) && find(placedItems.begin(), placedItems.end(), make_pair(itemX, itemY)) == placedItems.end()) {
                    char itemSymbol = static_cast<char>(rand() % 27 + 197); // Range from 197 to 223
                    map[itemY][itemX] = itemSymbol; // Place the item on the map
                    placedItems.push_back(make_pair(itemX, itemY)); // Track item placement
                    itemPlaced = true;
                }
                attempts++;
            }
            if (!itemPlaced) {
                cout << "Failed to place all items, placed " << placedItems.size() << " instead of " << numItems << endl;
            }
        }

        // Generate corridors between rooms
        for (size_t i = 0; i < rooms.size() - 1; ++i) {
            Room currentRoom = rooms[i];
            Room nextRoom = rooms[i + 1];

            // Calculate the starting and ending positions for the corridor
            int startX = currentRoom.x + currentRoom.width / 2;
            int startY = currentRoom.y + currentRoom.height / 2;
            int endX = nextRoom.x + nextRoom.width / 2;
            int endY = nextRoom.y + nextRoom.height / 2;

            // Draw horizontal corridor
            for (int x = min(startX, endX); x <= max(startX, endX); ++x) {
                map[startY][x] = EMPTY;
            }
            // Draw vertical corridor
            for (int y = min(startY, endY); y <= max(startY, endY); ++y) {
                map[y][endX] = EMPTY;
            }
        }

        // Fill in any isolated single-block paths
        for (int y = 1; y < MAP_HEIGHT - 1; ++y) {
            for (int x = 1; x < MAP_WIDTH - 1; ++x) {
                if (map[y][x] == WALL) {
                    if (map[y - 1][x] == EMPTY && map[y + 1][x] == EMPTY && map[y][x - 1] == EMPTY && map[y][x + 1] == EMPTY) {
                        map[y][x] = EMPTY; // Convert isolated single-block paths to empty space
                    }
                }
            }
        }

        interiorGenerated = true; // Set interiorGenerated flag to true
        backupInteriorMap(); // Backup the interior map
    }
}

// Method to pick up an item at the given position
bool GameWorld::pickUpItem(int x, int y) {
    if (map[y][x] != EMPTY) { // Check if there's an item at the given position
        map[y][x] = EMPTY; // Remove the item from the map
        numItemsPickedUp++; // Increment the counter
        return true; // Item picked up successfully
    }
    return false; // No item at the given position
}

// Method to generate enemies in the game world
void GameWorld::generateEnemies(int numEnemies, int bufferX, int bufferY, int safeZoneRadius) {
    enemies.clear(); // Clear the enemies vector
    for (int i = 0; i < numEnemies; ++i) {
        int enemyX, enemyY;
        do {
            enemyX = rand() % MAP_WIDTH;
            enemyY = rand() % MAP_HEIGHT;
        } while (isWall(enemyX, enemyY) || (abs(enemyX - bufferX) < safeZoneRadius && abs(enemyY - bufferY) < safeZoneRadius));
        enemies.emplace_back(enemyX, enemyY, *this); // Add a new enemy to the vector
    }
}

// Method to move enemies in the game world
void GameWorld::moveEnemies() {
    auto now = std::chrono::steady_clock::now(); // Get the current time
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastEnemyMoveTime) >= enemyMoveDelay) {
        for (auto& enemy : enemies) {
            enemy.moveTowardsPlayer(character); // Move each enemy towards the player
        }
        lastEnemyMoveTime = now; // Reset the last move time
    }
}

// Method to clear all enemies from the game world
void GameWorld::clearEnemies() {
    enemies.clear(); // Clear the enemies vector
}

// Method to backup the starting map
void GameWorld::backupStartingMap() {
    startingMapData = map; // Store the current map data
}

// Method to backup the interior map
void GameWorld::backupInteriorMap() {
    if (interiorGenerated) { // Check if the interior is generated
        interiorMapData = map; // Store the current map data
    }
}

// Method to restore the starting map from backup
void GameWorld::restoreStartingMap() {
    if (!startingMapData.empty()) { // Check if the starting map data is not empty
        map = startingMapData; // Restore the map from backup
    }
}

// Method to restore the interior map from backup
void GameWorld::restoreInteriorMap() {
    if (!interiorMapData.empty()) { // Check if the interior map data is not empty
        map = interiorMapData; // Restore the map from backup
    }
}

// Method to reset map generation flags
void GameWorld::resetMapGeneration() {
    mapGenerated = false; // Reset the mapGenerated flag
    interiorGenerated = false; // Reset the interiorGenerated flag
}

// Method to display and update the game map
void GameWorld::displayUpdateMap() const {
    system("cls"); // Clear the console screen
    // Iterate through the map and display each element
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == character.getY() && j == character.getX()) {
                cout << '@'; // Symbol representing the character
            }
            else {
                // Check if the position matches any enemy position
                bool isEnemy = false;
                for (const Enemy& enemy : enemies) {
                    if (i == enemy.getY() && j == enemy.getX()) {
                        cout << (char)159; // Display an enemy
                        isEnemy = true;
                        break;
                    }
                }

                if (!isEnemy) {
                    // Draw borders and other map elements
                    if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                        cout << (char)177; // Draw the border
                    }
                    else {
                        cout << map[i][j]; // Draw other map elements
                    }
                }
            }
        }
        cout << endl; // Add a newline character after each row
    }
}

// Method to set the position of the character
void GameWorld::setCharacterPosition(int x, int y) {
    character.setPosition(x, y); // Set the character position
}

// Method to update the character position based on user input
void GameWorld::updateCharacterPosition(char input) {
    switch (input) {
    case 'w':
        character.moveUp(*this); // Move character up
        break;
    case 's':
        character.moveDown(*this); // Move character down
        break;
    case 'a':
        character.moveLeft(*this); // Move character left
        break;
    case 'd':
        character.moveRight(*this); // Move character right
        break;
    default:
        // Handle other inputs if needed
        break;
    }
}

// Method to set the character object
void GameWorld::setCharacter(const Character& character) {
    this->character = character; // Set the character object
}

// Method to check if a position is a wall
bool GameWorld::isWall(int x, int y) const {
    return map[y][x] == WALL; // Return true if the position is a wall
}
