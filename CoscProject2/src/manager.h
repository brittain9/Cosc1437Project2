
#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;

#include "employee.h"

void PerformanceReview(double history, double performance);

enum level_t {
	team,
	middle,
	executive
};

class Manager : public Employee
{
	level_t level;
	std::vector<int> employeesIds; 

public:
	Manager(){}


	// for new managers
	Manager(std::string name, std::string position, int age, double salary, level_t level)
		: Employee(name, position, age, salary), level(level) {}

	// for reading from file
	Manager(int id, std::string name, std::string position, int age, double salary, int history, int performance, level_t level, vector<int> employeeIds) 
		: Employee(id, name, position, age, salary, history, performance), level(level), employeesIds(employeeIds) {}


	std::string getClassName() override { return "Manager"; }

	level_t getLevel() { return level; }
	std::vector<int> getEmployees() { return employeesIds; }

	void setLevel(level_t Level) { level = Level; }
	void addEmployee(int id) { employeesIds.push_back(id); }

	void printSubmenu() override;
	void printOptions() override;
	void printSubHeader() override;
	void printUserOptions() override;

	void createNew() override;
	std::string createLogString() override;

	// hire and fire
	// pay bonuses

};

#endif