#include "Employee.h"
#include <iomanip>
using std::setfill;
using std::setw;

#include "menu.h"

void Employee::printSubHeader() {
	cout << '\n' << setfill('=') << setw(50) << "\n";
	cout << setfill(' ') << setw(20) << "Welcome Employee" << std::endl;
	cout << setfill('=') << setw(50) << "\n\n";
}

void Employee::printOptions() { // get client, authentcation
	cout << "New employees please go through a manager for hiring.\n";
	cout << "1. Choose from an existing employee\n";
	cout << "2. Go back\n\n";
}

void Employee::printSubmenu() {

	printSubHeader();
	printOptions();
	int choice = getChoice("Enter your option: ", 2);

	switch (choice) {
		case 1:
			cout << "show a list of employees and select from this list\n";
			break;
		case 2:
			break;
	}
}
