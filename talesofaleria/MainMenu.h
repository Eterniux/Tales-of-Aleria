#pragma once // Preprocessor directive to ensure header file is included only once
#include <iostream> // For input/output operations

class MainMenu {
public:
    MainMenu(); // Constructor declaration
    void display() const; // Function to display the main menu
    int handleInput(); // Function to handle user input and return choice
};
