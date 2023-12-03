#include "organized.h"

/*
Managers can hire and fire employees and provide raises/ bonuses. This is all just going to be log editing. Find that employee in the log and change something or remove the entry entirely. Hiring is just creating new employees. Clients will be able to create projects so that will be in the client menu. Possibly in the client menu we need a spot to select if they are an existing client or create them as a new client.

Performance report? Maybe employees will have an option to report the work they do in some sort of vector. Then managers can just look at this. The results need to be avaliable to the employee. Make the report useful for determing whether they are at risk of being fired or deserve a raise. This just is a switch statement. List the top performers so that clients can choose.

Budget Analysis: Client should have option to check the budget analysis. Compare spent versus budget. Projection?
*/

int main() {
	bool running = true;
	CompanyLog* log = new CompanyLog("file.txt");
	log->readLines();
	log->parseLines();
	
	for (auto line : log->getLines()) {
		cout << line << "\n";
	}

	for (auto a : log->getLogs()) {
		std::string type = a->getClassName();
		if (type == "Client") {
			Client* c1 = static_cast<Client*>(a);
			std::string name = c1->getName();
			cout << name << "\n";
		}
		else if (type == "Employee") {
			Employee* e1 = static_cast<Employee*>(a);
			cout << e1->getName() << "\n";
		}
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