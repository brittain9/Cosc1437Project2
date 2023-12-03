#ifndef CLIENT_H
#define CLIENT_H

#include "organized.h"

class Client : public User, public ILoggable {
	std::string industry;
	std::vector<int> projectIds;
	//std::vector<int> employeeIds;

public:
	Client() {}

	Client(int id, std::string name, std::string industry, std::vector<int> projectIds) : ILoggable(id), User(name), industry(industry), projectIds(projectIds) {}

	std::string getClassName() override { return "Client"; }

	std::string getIndustry() { return industry; }
	void setIndustry(std::string Industry) { industry = Industry; }

	//std::vector<int> getEmployees() { return employeeIds; }
	//void setEmployees(std::vector<int> Employees) { employeeIds = Employees; }
	//void addEmployee(int eId) { employeeIds.push_back(eId); }
	
	std::vector<int> getProjects() { return projectIds; }
	void setProjects(std::vector<int> Projects) { projectIds = Projects; }
	void addProject(int pId) { projectIds.push_back(pId); }

	void printSubmenu() override;
	void printOptions() override;
	void printSubHeader() override;

	//void AddtoLog() override;
};

#endif
