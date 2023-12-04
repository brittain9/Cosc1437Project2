#include "Manager.h"
#include <iomanip>
using std::setfill;
using std::setw;

#include <sstream>

#include "menu.h"


void Manager::printSubHeader() {
	cout << '\n' << setfill('=') << setw(50) << "\n";
	cout << setfill(' ') << setw(20) << "Welcome Manager" << std::endl;
	cout << setfill('=') << setw(50) << "\n\n";
}

void Manager::printOptions() { // get client, authentcation
	cout << "1. Create a new manager\n";
	cout << "2. Choose from an existing manager\n";
	cout << "3. Go back\n\n";
}

void Manager::printSubmenu() {

	printSubHeader();
	printOptions();
	int choice = getChoice("Enter your option: ", 3);

	switch (choice) {
	case 1:
		cout << "prompt for new manager creation\n";
		break;
	case 2:
		cout << "show a list of employees and select from this list\n";
		break;
	case 3:
		break;
	}
}
void Manager::createNew() {
	cout << "implement\n";
}

std::string Manager::createLogString() {
	std::ostringstream oss;
	oss << getClassName() << " " << getId() << " \"" << getName() << "\" \"" << getPosition() << "\" " << getAge() << " " << getSalary() << " " << getHistory() << " " << getPerformance() << " " << static_cast<int>(getLevel()) << " ";

	for (int i = 0; i < employeesIds.size(); ++i) {
		oss << employeesIds[i];

		// Add a space after each id, except the last one
		if (i != employeesIds.size() - 1) {
			oss << " ";
		}
	}
	return oss.str();
}