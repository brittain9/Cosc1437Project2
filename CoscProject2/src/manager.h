
#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;

#include "employee.h"

enum level_t;

class Manager : public Employee
{
	level_t level;
	std::vector<int> employeesIds; 

public:
	Manager(){}
	Manager(int id, std::string name, std::string position, int age, double salary, int history, int performance, level_t level, vector<int> employeeIds) : Employee(id, name, position, age, salary, history, performance), level(level), employeesIds(employeesIds) {}

	std::string getClassName() override { return "Manager"; }

	level_t getLevel() { return level; }
	std::vector<int> getEmployees() { return employeesIds; }

	void setLevel(level_t Level) { level = Level; }

	void printSubmenu() override;
	void printOptions() override;
	void printSubHeader() override;

	// hire and fire
	// pay bonuses
	enum level_t {
		team,
		middle,
		executive
	};
};

#endif