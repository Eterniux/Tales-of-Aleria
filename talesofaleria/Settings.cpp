#include "Settings.h" // Including Settings header file
#include "Character.h" // Including Character header file
#include "CharacterCreation.h" // Including CharacterCreation header file
#include <fstream> // For file input/output operations
#include <iostream> // For input/output operations
#include <string> // For string manipulation
#include <limits> // For numeric_limits
using namespace std;

// Declare settings object and character creation instance
Settings settings;
CharacterCreation& characterCreation = CharacterCreation::getInstance();

// Settings constructor
Settings::Settings() {
    // Initialize default keybinds
    keybinds.moveUp = 'w';
    keybinds.moveDown = 's';
    keybinds.moveLeft = 'a';
    keybinds.moveRight = 'd';

    // Attempt to load settings from file
    loadSettings();
}

// Display settings menu
void Settings::display() const {
    cout << "========================================================" << endl;
    cout << "                Tales of Aleria - Settings              " << endl;
    cout << "========================================================" << endl;
    cout << endl;
}

// Handle user input in settings menu
int Settings::handleInput() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Set new keybindings
void Settings::setKeybinds(const Keybinds& newKeybinds) {
    this->keybinds = newKeybinds;
    saveSettings();
}

// Get current keybindings
Keybinds Settings::getKeybinds() const {
    return keybinds;
}

// Edit keybindings
void Settings::editKeybinds() {
    Keybinds currentKeybinds = getKeybinds();
    int keybindChoice;
    do {
        // Clear the console
        system("cls");
        cout << "========================================================" << endl;
        cout << "              Tales of Aleria - Edit Keybinds           " << endl;
        cout << "========================================================" << endl;
        cout << "Select the action you want to change the keybind for:" << endl;
        cout << "1. Move Up (Current key: " << currentKeybinds.moveUp << ")" << endl;
        cout << "2. Move Down (Current key: " << currentKeybinds.moveDown << ")" << endl;
        cout << "3. Move Left (Current key: " << currentKeybinds.moveLeft << ")" << endl;
        cout << "4. Move Right (Current key: " << currentKeybinds.moveRight << ")" << endl;
        cout << "5. Return to Settings Menu" << endl;
        cout << "Enter your choice: ";
        cin >> keybindChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        char newKey;
        switch (keybindChoice) {
        case 1:
            cout << "Enter new key for moving up: ";
            cin >> newKey;
            currentKeybinds.moveUp = newKey;
            break;
        case 2:
            cout << "Enter new key for moving down: ";
            cin >> newKey;
            currentKeybinds.moveDown = newKey;
            break;
        case 3:
            cout << "Enter new key for moving left: ";
            cin >> newKey;
            currentKeybinds.moveLeft = newKey;
            break;
        case 4:
            cout << "Enter new key for moving right: ";
            cin >> newKey;
            currentKeybinds.moveRight = newKey;
            break;
        case 5:
            setKeybinds(currentKeybinds); // Save keybinds after changes
            return; // Exits the method
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
        }

        setKeybinds(currentKeybinds); // Save keybinds after changes
        // Clear the console
        system("cls");
    } while (keybindChoice != 5);
}

// Display settings
void Settings::display(bool inGame) const {
    cout << "========================================================" << endl;
    cout << "                Tales of Aleria - Settings              " << endl;
    cout << "========================================================" << endl;
    cout << endl;

    if (inGame) {
        cout << "================================\n";
        cout << "| Player: " << characterCreation.getCharacterName() << "  Class: " << characterCreation.getChosenClass() << "\n"; // Display the character's name and class
        cout << "================================\n";
        cout << "1. Resume Game" << endl;
        cout << "2. Change Keybinds" << endl;
        cout << "3. Go to Main Menu" << endl;
        cout << "4. Exit" << endl;
    }
    else {
        // Game is not active
        cout << "1. Change Keybinds" << endl;
        cout << "2. Go to Main Menu" << endl;
        cout << "3. Exit" << endl;
    }
}

// Save settings to file
void Settings::saveSettings() {
    ofstream outFile("settings.txt"); // Open in default mode (truncation)
    // Write the current settings to the file
    outFile << "MoveUp=" << keybinds.moveUp << endl;
    outFile << "MoveDown=" << keybinds.moveDown << endl;
    outFile << "MoveLeft=" << keybinds.moveLeft << endl;
    outFile << "MoveRight=" << keybinds.moveRight << endl;
    outFile.close();
}

// Load settings from file
void Settings::loadSettings() {
    ifstream inFile("settings.txt");
    string line;
    if (inFile) {
        while (getline(inFile, line)) {
            auto delimiterPos = line.find('=');
            string key = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1);

            if (key == "MoveUp") {
                keybinds.moveUp = value[0];
            }
            else if (key == "MoveDown") {
                keybinds.moveDown = value[0];
            }
            else if (key == "MoveLeft") {
                keybinds.moveLeft = value[0];
            }
            else if (key == "MoveRight") {
                keybinds.moveRight = value[0];
            }
        }
        inFile.close();
    }
    else {
        cout << "No save file found. Using default settings.\n";
    }
}
