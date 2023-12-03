
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include <iostream>
using std::cout;


#include "user.h"
#include "ILoggable.h"

class Employee : public User, public ILoggable
{
	std::string position;
	int age;
	double salary;
	int history; // years at the company
	int performance; // what does this mean? like performance of 10 represents what? maybe an enum here. Maybe two other vars for time worked and billable hours?
public:
	Employee() {}
	Employee(int id, std::string name, std::string position, int age, double salary, int history, int performance) :  ILoggable(id), User(name), position(position), age(age), salary(salary), history(history), performance(performance) {}

	std::string getClassName() override { return "Employee"; }

	std::string getPosition()  { return position; }
	int getHistory() { return history; }
	int getAge() { return age; }
	double getSalary() { return salary; }
	int getPerformance() { return performance; }

	void setPosition(std::string Position) { position = Position; }
	void setHistory(int History) { history = History; }
	void setAge(int Age) { age = Age; }
	void setSalary(double Salary) { salary = Salary; }
	void setPerformance(int Perf) { performance = Perf; }

	void printSubmenu() override;
	void printOptions() override;
	void printSubHeader() override;
	//void AddtoLog() override;
};

#endif
