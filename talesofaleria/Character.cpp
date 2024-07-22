#include "Character.h"
#include "GameWorld.h"


// Parameterized constructor for Character class
Character::Character(const std::string& name, const std::string& characterClass)
    : name(name), characterClass(characterClass), x(0), y(0), worldWidth(MAP_WIDTH), worldHeight(MAP_HEIGHT) {
 
}

// Getter for character's x-coordinate
int Character::getX() const {
    return x;
}

// Getter for character's y-coordinate
int Character::getY() const {
    return y;
}

// Setter for character's position
void Character::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

// Method to move the character up
void Character::moveUp(GameWorld& world) {
    if (y > 1 && !world.isWall(x, y - 1)) {
        y--;
    }
}
// Method to move the character down
void Character::moveDown(GameWorld& world) {
    if (y < worldHeight - 2 && !world.isWall(x, y + 1)) {
        y++;
    }
}
// Method to move the character left
void Character::moveLeft(GameWorld& world) {
    if (x > 1 && !world.isWall(x - 1, y)) {
        x--;
    }
}
// Method to move the character right
void Character::moveRight(GameWorld& world) {
    if (x < worldWidth - 2 && !world.isWall(x + 1, y)) {
        x++;
    }
}