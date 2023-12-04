#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
using std::cout;

void printMenu();
std::string getString(const std::string& prompt);
int getChoice(std::string prompt, int maxOptions);


template <typename T>
T getInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please try again." << std::endl;
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

#endif