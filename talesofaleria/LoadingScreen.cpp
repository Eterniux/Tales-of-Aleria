#include <iostream> // For input/output operations
#include <chrono> // For time-related functionality
#include <thread> // For multi-threading support
#include "LoadingScreen.h" // Including LoadingScreen header file
using namespace std;

// Constructor definition
LoadingScreen::LoadingScreen() {}

// Function to display the loading screen
void LoadingScreen::display() const {
    const int LoadingWidth = 30; // Width of the loading animation
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "                                               Loading Tales of Aleria...\n\n"; // Display loading message
    cout << "                                           ["; // Display loading animation start

    // Display loading animation
    for (int i = 0; i < LoadingWidth; ++i) {
        std::cout << "\033[1;31m#\033[0m"; // Display '#' with red color
        this_thread::sleep_for(chrono::milliseconds(100)); // Add delay for each character
    }

    cout << "]"; // Display loading animation end
    this_thread::sleep_for(chrono::milliseconds(100)); // Add delay after loading animation
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "" << endl; // Empty line
    cout << "                                                   Game has Loaded!" << endl; // Display game loaded message
}
