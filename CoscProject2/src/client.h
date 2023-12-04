#ifndef CLIENT_H
#define CLIENT_H

#include "ILoggable.h"
#include "user.h"

class Client : public User, public ILoggable {
	std::string industry;
	std::vector<int> projectIds;

	void printOptions() override;
	void printSubHeader() override;
	void printUserOptions() override;
public:
	Client() {}

	// for reading from file
	Client(int id, std::string name, std::string industry, std::vector<int> projectIds) 
		: ILoggable(id), User(name), industry(industry), projectIds(projectIds) {}

	// for creating new clients
	Client(std::string name, std::string industry) 
		: ILoggable(), User(name), industry(industry) {}

	std::string getClassName() override { return "Client"; }

	std::string getIndustry() { return industry; }
	std::vector<int> getProjects() { return projectIds; }

	void setIndustry(std::string Industry) { industry = Industry; }
	void setProjects(std::vector<int> Projects) { projectIds = Projects; }
	void addProject(int pId) { projectIds.push_back(pId); }

	void printSubmenu() override;


	void createNew() override;
	std::string createLogString() override;
};

#endif
