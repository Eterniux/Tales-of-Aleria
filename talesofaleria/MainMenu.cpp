#include "MainMenu.h" // Including MainMenu header file
#include <iostream> // For input/output operations
using namespace std;

// Constructor definition
MainMenu::MainMenu() {}

// Function to display the main menu
void MainMenu::display() const {
    cout << "========================================================" << endl;
    cout << "                Tales of Aleria - Main Menu             " << endl;
    cout << "========================================================" << endl;

    // Main menu options with red numbers
    cout << endl;
    cout << "\033[1;37m\033[1;31m1.\033[0m New Game" << endl;                       // Red color for number 1
    cout << "\033[1;37m\033[1;31m2.\033[0m Settings" << endl;                       // Red color for number 2
    cout << "\033[1;37m\033[1;31m3.\033[0m Algorithm Showcase" << endl;             // Red color for number 3
    cout << "\033[1;37m\033[1;31m4.\033[0m Exit" << endl;                           // Red color for number 4
    cout << endl;
}

// Function to handle user input and return choice
int MainMenu::handleInput() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice; // Just return the choice
}
