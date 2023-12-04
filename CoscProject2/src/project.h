#ifndef PROJECT_H
#define PROJECT_H

#include "organized.h"
using std::string;
using std::vector;

class Project : public ILoggable
{
	std::string name;
	int status; // percent of project done?
	double budget;
	double totalSpent;
	std::vector<int> employeesIds;
	// Client owner; // make this dynamic

public:
	Project() {}
	Project(int id, string name, int status, double budget,  double totalSpent, vector<int> employeeIds) 
		: ILoggable(id), name(name), status(status), budget(budget), totalSpent(totalSpent), employeesIds(employeeIds) {}

	Project( string name, int status, double budget, double totalSpent, vector<int> employeeIds) 
		: ILoggable(), name(name), status(status), budget(budget), totalSpent(totalSpent), employeesIds(employeeIds) {}

	// copy constructor
	Project(const Project& other)
		: ILoggable(other.id),
		name(other.name),
		status(other.status),
		budget(other.budget),
		totalSpent(other.totalSpent),
		employeesIds(other.employeesIds) {}

	std::string getClassName() override { return "Project"; }

	std::string getName() { return name; }
	int getStatus() { return status; }
	double getBudget() { return budget; }
	double getTotalSpent() { return totalSpent; }
	std::vector<int> getEmployees() { return employeesIds; }

	void setName(const std::string& name) { this->name = name; }
	void setStatus(int status) { this->status = status; }
	void setBudget(double budget) { this->budget = budget; }
	void setTotalSpent(double totalSpent) { this->totalSpent = totalSpent; }
	void setEmployees(const std::vector<int>& employeesIds) { this->employeesIds = employeesIds; }
	void addEmployee(int employeeId) { employeesIds.push_back(employeeId); }

	void createNew() override;
	std::string createLogString() override;
};

#endif