#include "charactercreation.h" // Include header file for CharacterCreation class
#include <chrono> // Include chrono library for time-related operations
#include <thread> // Include thread library for managing threads
using namespace std; // Using standard namespace


// Method to start the character creation process
void CharacterCreation::startCharacterCreation() {
    const int LoadingWidth = 30; // Define the width of the loading animation
    cout << "" << endl; // Displaying multiple empty lines for visual separation
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "                                               Starting a new game. \n\n"; // Displaying a message indicating the start of the game
    cout << "                                           ["; // Start of the loading animation

    // Loop to display the loading animation
    for (int i = 0; i < LoadingWidth; ++i) {
        std::cout << "\033[1;31m#\033[0m"; // Display '#' sign in red color
        this_thread::sleep_for(chrono::milliseconds(100)); // Delay between displaying '#' signs
    }

    cout << "]"; // End of the loading animation
    this_thread::sleep_for(chrono::milliseconds(100)); // Delay for visual effect
    cout << "" << endl; // Displaying three empty lines for visual separation
    cout << "" << endl;
    cout << "" << endl;
    system("cls"); // Clear console screen

    bool confirmed = false; // Flag to track whether character creation is confirmed
    while (!confirmed) { // Loop until character creation is confirmed
        chooseCharacterName(); // Call method to choose character name
        chooseCharacterClass(); // Call method to choose character class
        confirmed = displayCharacterSummary(); // Call method to display character summary and get confirmation
        if (!confirmed) {
        }
    }
    // Proceed to the next part of the game
}

// Method to create the character
Character CharacterCreation::createCharacter() {
    return Character(characterName, chosenClass); // Create and return a Character object
}

// Method to choose the character's name
void CharacterCreation::chooseCharacterName() {
    // Display character creation screen and prompt for name
    cout << "========================================================" << endl;
    cout << "             Tales of Aleria - Character Creation       " << endl;
    cout << "========================================================" << endl;

    cout << "Enter your character's name: "; // Prompt for entering character name
    cin >> characterName; // Get character name from user input
    system("cls"); // Clear console screen
}

// Method to choose the character's class
void CharacterCreation::chooseCharacterClass() {
    // Display character creation screen and prompt for class choice
    cout << "========================================================" << endl;
    cout << "             Tales of Aleria - Character Creation       " << endl;
    cout << "========================================================" << endl;

    cout << "Choose your character class:" << std::endl; // Prompt for choosing character class

    cout << "\033[1;31m1.\033[0m Warrior\n"; // Red color for option 1
    cout << "\033[1;31m2.\033[0m Mage\n";    // Red color for option 2
    cout << "\033[1;31m3.\033[0m Rogue\n";    // Red color for option 3

    int choice;
    cin >> choice; // Get user's class choice

    // Switch case to set chosen class based on user's choice
    switch (choice) {
    case 1:
        chosenClass = "Warrior";
        break;
    case 2:
        chosenClass = "Mage";
        break;
    case 3:
        chosenClass = "Rogue";
        break;
    default:
        // Handle invalid input
        cout << "Invalid choice. Please select a valid option." << std::endl;
        return;
    }
    system("cls"); // Clear console screen
}

// Method to display character summary and get confirmation
bool CharacterCreation::displayCharacterSummary() {
    // Display character summary with name and class
    std::cout << "========================================================" << std::endl;
    std::cout << "            Tales of Aleria - Character Summary         " << std::endl;
    std::cout << "========================================================" << std::endl;
    std::cout << "Character Name: " << characterName << std::endl;
    std::cout << "Character Class: " << chosenClass << std::endl;
    std::cout << "Is this correct? (Y/N): ";

    char choice;
    cin >> choice;

    system("cls"); 

    // Simple validation for 'Y' or 'y' indicating confirmation
    return (choice == 'Y' || choice == 'y');
}
