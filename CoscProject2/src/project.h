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
	Project(int id, string name, int status, double budget,  double totalSpent, vector<int> employeeIds) : ILoggable(id), name(name), status(status), budget(budget), totalSpent(totalSpent), employeesIds(employeesIds) {}

	std::string getClassName() override { return "Project"; }

	// TODO: Getters and setters
};

#endif