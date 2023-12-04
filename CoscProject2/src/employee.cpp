#include "Employee.h"
#include <iomanip>
using std::setfill;
using std::setw;

#include <sstream>

#include "menu.h"
#include "company_log.h"
#include "manager.h"
#include "project.h"

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

#define EMPLOYEE_OPTIONS 3
void Employee::printUserOptions() {
	cout << "\n1. Submit work on a project\n";
	cout << "2. Request Performance review\n";
	cout << "3. Return to main menu\n\n";
}

void Employee::printSubmenu() {

	printSubHeader();
	printOptions();
	int choice = getChoice("Enter your option: ", 2);

	std::vector<ILoggable*> employeesList;
	Employee* employee = nullptr;
	switch (choice) {
	case 1:
		// choose from existing client
		employeesList = CompanyLog::getInstancesOfType("Employee");
		if (employeesList.size() > 0) {
			cout << '\n' << setfill('=') << setw(30) << "\n";
			cout << "\nSelect from the list.\n\n";
			for (int i = 0; i < employeesList.size(); i++) {
				Employee* e = static_cast<Employee*>(employeesList[i]);
				cout << i + 1 << ". " << e->getName() << " | Position: " << e->getPosition() << '\n'; // i + 1 so our list starts with 1
			}
			int employeeChoice = getChoice("\nEnter your employee number: ", employeesList.size());
			employee = static_cast<Employee*>(employeesList[employeeChoice - 1]); // the 1st client is 0 is our vector so we substract by 1
		}
		else
			cout << "\nNo existing employees. Manager needs to hire some.\n";
		break;
	case 2:
		return;
	}
	// add the options menu for employees.
	cout << '\n' << setfill('=') << setw(50) << "\n";
	cout << setfill(' ') << setw(20) << "Welcome " << employee->getName() << "!" << std::endl;
	cout << setfill('=') << setw(50) << "\n";
	choice = -1; // set not equal to CLIENT_OPTIONS

	std::vector<ILoggable*> projectsList;

	while (choice != EMPLOYEE_OPTIONS) {
		printUserOptions();
		choice = getChoice("Enter your option: ", EMPLOYEE_OPTIONS);

		switch (choice) {
		case 1: 
			{
				projectsList = CompanyLog::getInstancesOfType("Project");
				std::vector<Project*> currProjs;
				// get all our projects and create a vector for this employ's projs

				for (int i = 0; i < projectsList.size(); i++) {
					Project* p = static_cast<Project*>(projectsList[i]);
					if (p->getStatus() >= 100) continue; // this project is done, no need to work on it
					std::vector<int> employeesOnProj = p->getEmployees();
					// loop through all projects and all ids of projects to see if our current employee is in there
					for (int j = 0; j < employeesOnProj.size(); j++) {
						if (employeesOnProj[j] == employee->getId()) {
							// is so add that project to the projects
							currProjs.push_back(p);
						}
					}
				}
				Project* workingOn = nullptr;
				// print out the projects
				if (currProjs.size() > 0) {
					cout << "\nCurrent projects you are assigned to:\n";
					for (int i = 0; i < currProjs.size(); i++) {
						cout << i + 1 << ". " << currProjs[i]->getName() << " | Status: " << currProjs[i]->getStatus() << '\n';
					}
					int projChoice = getChoice("Enter the number of the project you are working on: ", currProjs.size());
					workingOn = currProjs[projChoice - 1];
				}

				int hours = getInput<int>("Enter the hours you worked this week: ");
				// depending on your hours you work. You get a bit of a boost to your score.
				if (hours > 70) employee->setPerformance(employee->getPerformance() + 4);
				else if (hours > 60) employee->setPerformance(employee->getPerformance() + 3);
				else if (hours > 50) employee->setPerformance(employee->getPerformance() + 2);
				else if (hours > 40) employee->setPerformance(employee->getPerformance() + 1);
				else employee->setPerformance(employee->getPerformance() - 1);
				cout << "\nYou have a performance score of " << employee->getPerformance() << "!\n";

				if (workingOn != nullptr) {
					// every project is going to take a constant 1000 hours of work.
					double addedToStatus = (hours / 1000.0) * 100; // this a percentage
					int newStatus = workingOn->getStatus() + (int)addedToStatus;
					if (newStatus > 100) newStatus = 100;

					workingOn->setStatus(newStatus);
					cout << "New status: " << workingOn->getStatus() << '\n';

					CompanyLog::addToLog(workingOn);
					WriteToLog(workingOn);
				}

				CompanyLog::addToLog(employee);
				WriteToLog(employee);
			}
			break;
		case 2:
			cout << "\nRunning performance review on " << employee->getName() << "!\n";

			PerformanceReview(employee->getHistory(), employee->getPerformance());
			break;
		case 3:
			break;

		}
	}
}

void Employee::createNew() {
	std::string name = getString("Enter your name: ");
	std::string position = getString("Enter your position: ");
	int age = getInput<int>("Enter your age: ");
	double salary = getInput<double>("Enter your salary: ");

	Employee* newEmployee = new Employee(name, position, age, salary);
	CompanyLog::addToLog(newEmployee);
	WriteToLog(newEmployee);
}

std::string Employee::createLogString() {
	std::ostringstream oss;
	oss << getClassName() << " " << getId() << " \"" << getName() << "\" \"" << getPosition() << "\" " << getAge() << " " << getSalary() << " " << getHistory() << " " << getPerformance();

	return oss.str();
}