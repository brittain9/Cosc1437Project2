#ifndef MENU_H
#define MENU_H

#include "organized.h"

void printMenu();
std::string getString(std::string prompt);
int getChoice(std::string prompt, int maxOptions);

#endif