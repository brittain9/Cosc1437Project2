#include "menu.h"

void printMenuHeader() {
	cout << '\n' << setfill('=') << setw(50) << "\n";
	cout << setfill(' ') << setw(20) << "Welcome to Alex's Company Project Management System!" << std::endl;
	cout << setfill('=') << setw(50) << "\n\n";
}

std::string getString(std::string prompt) {
    cout << prompt;
    std::string str1;
    std::getline(std::cin, str1);
    return str1;
}

int getChoice(std::string prompt, int maxOptions) {
    // Get valid user input from choice selection of 1 to maxOptions
    cout << prompt;

    // Loop for getting valid input
    int choice = -1;
    while (choice < 1 || choice > maxOptions) {
        std::string input;
        std::cin >> input;
        try {
            choice = std::stoi(input);
        }
        catch (const std::invalid_argument& e) {} // loop will continue if input is invalid

        if (choice < 1 || choice > maxOptions) {
            std::cout << "Enter an option between 1 and " << maxOptions << ": ";
        }
    }
    // Clear the input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return choice;
}

void printMenuOptions() {
	cout << "1. Client\n";
	cout << "2. Employee\n";
	cout << "3. Manager\n";
	cout << "4. Exit Application\n\n";
}

void printMenu() {
	printMenuHeader();
    printMenuOptions();
}