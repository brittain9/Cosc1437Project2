#include "organized.h"
#include "menu.h"
#include "company_log.h"

/*
TODO:
Figure out a way to 
*/

int main() {
	bool running = true;
	CompanyLog* log = new CompanyLog("file.txt");
	log->readLines();
	log->parseLines();

	for (auto a : log->getLogs()) {
		cout << a->createLogString() << '\n';
	}

	do
	{
		printMenu();
		int choice = getChoice("Please enter your role: ", 4);
		User* user = nullptr;
		switch (choice)
		{
			case 1:
				user = new Client();
				break;
			case 2:
				user = new Employee();
				break;
			case 3:
				user = new Manager();
				break;
			case 4:
				cout << "\nExiting Application...\n";
				running = false;
				break;
		}
		if (running) {
			user->printSubmenu();
		}

	} while (running);

	return 0;
}