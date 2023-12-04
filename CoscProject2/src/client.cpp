#include "client.h"
#include "menu.h"

#include "company_log.h"
#include "project.h"

#include <iomanip>
using std::setfill;
using std::setw;
#include <sstream>

void BudgetAnalysis(double status, double budget, double totalSpent) {
	double projectedSpent = (totalSpent / (status / 100));
	double difference = projectedSpent - budget;

	if (difference > 0) {
		std::cout << "You are spending too quickly. You are projected to go over budget by $" << difference << "." << std::endl;
	}
	else if (difference < 0) {
		std::cout << "You can spend more. You are projected to be under budget by $" << -difference << "." << std::endl;
	}
	else {
		std::cout << "Your spending is on track with the budget." << std::endl;
	}
}

void Client::printSubHeader() {
	cout << '\n' << setfill('=') << setw(50) << "\n";
	cout << setfill(' ') << setw(20) << "Welcome Client" << std::endl;
	cout << setfill('=') << setw(50) << "\n\n";
}

void Client::printOptions() { // get client, authentcation
	cout << "1. New Client Registration\n";
	cout << "2. Choose from an existing client\n";
	cout << "3. Go back\n\n";
}

void printUserOptions() {
	cout << "\n1. Add a new project\n";
	cout << "2. View existing projects\n";
	cout << "3. Add employees to a project\n"; // this needs to be done after our performance review feature
	// get recommended employees? top performers?
	cout << "4. Run a budget analysis on a project\n";
	cout << "5. Return to main menu\n\n";
}

void Client::printSubmenu() {

	printSubHeader();
	printOptions();
	int choice = getChoice("Enter your option: ", 3);
	
	std::vector<ILoggable*> clientsList; // for choosing a client
	Client* client = nullptr;
	switch (choice) {
		case 1:
			createNew();
			client = static_cast<Client*>(CompanyLog::getLogs()[CompanyLog::getLogs().size() - 1]); // set the client equal to this new client created, which should be the last thing on the logs vector since createNew() pushes back
			break;
		case 2:
			// choose from existing client
			clientsList = CompanyLog::getInstancesOfType("Client");
			if (clientsList.size() > 0) {
				cout << '\n' << setfill('=') << setw(30) << "\n";
				cout << "\nSelect your client from the list.\n\n";
				for (int i = 0; i < clientsList.size(); i++) {
					Client* c = static_cast<Client*>(clientsList[i]);
					cout << i + 1 << ". " << c->getName() << " " << c->getIndustry() << '\n'; // i + 1 so our list starts with 1
				}
				int clientchoice = getChoice("\nEnter your client number: ", clientsList.size());
				client = static_cast<Client*>(clientsList[clientchoice - 1]); // the 1st client is 0 is our vector so we substract by 1
			}
			else 
				cout << "\nNo existing clients. Please create a new client.\n";
			break;
		case 3:
			break;
	}
	cout << '\n' << setfill('=') << setw(50) << "\n";
	cout << setfill(' ') << setw(20) << "Welcome " << client->getName() << "!" << std::endl;
	cout << setfill('=') << setw(50) << "\n";
	// once we get authenticated, we offer some options.
	choice = -1; // set not equal to 4
	while (choice != 5) {


		printUserOptions();
		choice = getChoice("Enter your option: ", 5);

		Project* proj = new Project(); // option 1
		std::vector<ILoggable*> projects; // option2 
		switch (choice) {
			case 1:
				// create a project
				proj->createNew();
				proj = static_cast<Project*>(CompanyLog::getLogs()[CompanyLog::getLogs().size() - 1]);
				client->addProject(proj->getId());
				CompanyLog::addToLog(client);
				WriteToLog(client);
			continue;
			case 2:
				if (client->getProjects().size() > 0) {
					projects = CompanyLog::getInstancesFromIds(client->getProjects());
					for (int i = 0; i < projects.size(); i++) {
						Project* project = static_cast<Project*>(projects[i]);
						cout << i + 1 << ". " << project->getName() << " Status: " << project->getStatus() << "%" << '\n';
					}
				}
				else 
					cout << "Client doesn't have any projects\n";

			case 3:
			case 4:
				
				break;
		}
	}
}

void Client::createNew() {
	// this needs to prompt the user for input and pass to constructor. Then add to log and vector of logs.
	std::string name = getString("Enter your name: ");
	std::string industry = getString("Enter your industry: ");

	Client* newClient = new Client(name, industry);
	CompanyLog::addToLog(newClient);
	WriteToLog(newClient);
}

std::string Client::createLogString() {
	std::ostringstream oss;
	oss << getClassName() << " " << getId() << " \"" <<getName() << "\" \"" << getIndustry() << "\" ";
	for (int i = 0; i < projectIds.size(); ++i) {
		oss << projectIds[i];

		// Add a space after each id, except the last one
		if (i != projectIds.size() - 1) {
			oss << " ";
		}
	}
	return oss.str();
}