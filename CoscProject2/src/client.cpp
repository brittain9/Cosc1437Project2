#include "client.h"

//Client createNewClient() {
//	Client newClient;
//	newClient.setName(getString("Enter the name of the new client: "));
//	newClient.setIndustry(getString("Enter the industry of the new client: "));
//	CompanyLog.
//}

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

void Client::printSubmenu() {

	printSubHeader();
	printOptions();
	int choice = getChoice("Enter your option: ", 3);
	
	switch (choice) {
		case 1:
			cout << "prompt the user for new client info\n";
			break;
		case 2:
			cout << "show a list of clients and select from this list\n";
			break;
		case 3:
			break;
	}
}

//void Client::AddtoLog() {
//	cout << "not implemented";
//}