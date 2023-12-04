#include "manager.h"
#include <iomanip>
using std::setfill;
using std::setw;

#include <sstream>

#include "menu.h"
#include "company_log.h"

void PerformanceReview(double history, double performance) {
	cout << '\n' << setfill('=') << setw(50) << "\n";

	if (history == 0 && performance == 0) { // this is a new employee
		std::cout << "New employee. Please continue working for the company to get performance review\n" << std::endl;
		cout << setfill('=') << setw(50) << "\n\n";

		return;
	}
	
	if (performance > 20) {	// they've been working hard!
		std::cout << "This employee is hard-working. They can expect a nice bonus!";
	}
	else if (performance > 10) {
		std::cout << "This employee is good. They might get a bonus.";
	}
	else if (performance > 5) {
		std::cout << "Adequate performance";
	}
	else if(performance > 0){
		std::cout << "This employee needs to work harder.";
	}
	else {
		std::cout << "This employee needs to be monitored. Consider firing this employee.";
	}
	if (history > 10) {
		std::cout << "\nThis employee is very loyal to our company.";
	}
	else if(history > 5){
		std::cout << "\nThis employee is loyal to our company.";
	}
	else if (history > 3) {
		std::cout << "\nThis employee has some experience with us.";
	}
	cout << setfill('=') << setw(50) << "\n\n";
}

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

#define MANAGER_OPTIONS 6
void Manager::printUserOptions() {
	cout << "\n1. Hire an employee\n";	
	cout << "2. List employees under supervision\n";
	cout << "3. Fire an employee\n";
	cout << "4. Run a performance review\n";
	cout << "5. Give a bonus\n";
	cout << "6. Return to main menu\n\n";
}

void Manager::printSubmenu() {

	printSubHeader();
	printOptions();
	int choice = getChoice("Enter your option: ", 3);

	std::vector<ILoggable*> managerList; // for choosing a client
	Manager* manager = nullptr;
	switch (choice) {
	case 1:
		createNew();
		manager = static_cast<Manager*>(CompanyLog::getLogs()[CompanyLog::getLogs().size() - 1]);
		break;
	case 2:
		// choose from existing manager
	
		managerList = CompanyLog::getInstancesOfType("Manager");
		if (managerList.size() > 0) {
			cout << '\n' << setfill('=') << setw(30) << "\n";
			cout << "\nSelect your client from the list.\n\n";
			for (int i = 0; i < managerList.size(); i++) {
				Manager* c = static_cast<Manager*>(managerList[i]);
				cout << i + 1 << ". " << c->getName() << " | Position: " << c->getPosition() << '\n'; // i + 1 so our list starts with 1
			}
			int managerchoice = getChoice("\nEnter your manager number: ", managerList.size());
			manager = static_cast<Manager*>(managerList[managerchoice - 1]); // the 1st client is 0 is our vector so we substract by 1
		}
		else
			cout << "\nNo existing clients. Please create a new client.\n";
		break;
	case 3:
		return;
	}

	cout << '\n' << setfill('=') << setw(50) << "\n";
	cout << setfill(' ') << setw(20) << "Welcome " << manager->getName() << "!" << std::endl;
	cout << setfill('=') << setw(50) << "\n";

	// once we get authenticated, we offer some options.
	choice = -1; // set not equal to CLIENT_OPTIONS
	std::vector<ILoggable*> employees; // option2 
	while (choice != MANAGER_OPTIONS) {
		printUserOptions();
		choice = getChoice("Enter your option: ", MANAGER_OPTIONS);

		Employee* emp = new Employee(); // option 1
		switch (choice) {
		case 1:
			// create an employee/hire
			emp->createNew();
			emp = static_cast<Employee*>(CompanyLog::getLogs()[CompanyLog::getLogs().size() - 1]);
			CompanyLog::addToLog(emp);
			WriteToLog(emp);

			// add the employ then write it to log
			manager->addEmployee(emp->getId());
			CompanyLog::addToLog(manager);
			WriteToLog(manager);
			continue;
		case 2:
			if (manager->getEmployees().size() > 0) {
				employees = CompanyLog::getInstancesFromIds(manager->getEmployees());
				cout << "\n\nYou manage " << manager->getEmployees().size() << " employees:\n";
				for (int i = 0; i < employees.size(); i++) {
					Employee* employee = static_cast<Employee*>(employees[i]);
					cout << i + 1 << ". " << employee->getName() << " Position: " << employee->getPosition() << '\n';
				}
			}
			else
				cout << "Manager doesn't manager any employees\n";
			break;
		case 3:
		case 4:
			if (employees.size() > 0) {
				int employCoice = getChoice("\nSelect a employee from the list from option 2: ", employees.size());
				Employee* employee = static_cast<Employee*>(employees[employCoice - 1]);
				cout << "\nRunning performance review on " << employee->getName() << "!\n";

				PerformanceReview(employee->getHistory(), employee->getPerformance());
			}
			else {
				cout << "\nDo you have any employees? Run option 2 first.\n";
			}
		case 5:
			break;
		case 6:
			break;
		}
	}

}
void Manager::createNew() {
	// this needs to prompt the user for input and pass to constructor. Then add to log and vector of logs.
	std::string name = getString("Enter the name: ");
	std::string position = getString("Enter the position: ");
	int age = getInput<int>("Enter the age: ");
	double salary = getInput<double>("Enter the salary: ");

	level_t level = static_cast<level_t>(getInput<int>("Enter the manager level, 0 for team lead, 1 for midddle manager, 2 for executive: "));


	Manager* newManager = new Manager(name, position, age, salary, level);
	CompanyLog::addToLog(newManager);
	WriteToLog(newManager);
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