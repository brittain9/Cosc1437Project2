#include "project.h"

#include "menu.h"
#include "company_log.h"

void Project::createNew() {
	std::string name = getString("Enter the project name: ");
	double budget = getInput<double>("Enter your budget: ");
	std::vector<int> employeeIds;

	Project* newProject = new Project(name, 0, budget, 0.0, employeeIds);
	CompanyLog::addToLog(newProject);
	WriteToLog(newProject);
}

std::string Project::createLogString() {
	std::ostringstream oss;
	oss << getClassName() << " " << getId() << " \"" << getName() << "\" " << getStatus() << " " << getBudget() << " " << getTotalSpent() << " ";
	for (int i = 0; i < getEmployees().size(); ++i) {
		oss << getEmployees()[i];

		// Add a space after each id, except the last one
		if (i != getEmployees().size() - 1) {
			oss << " ";
		}
	}
	return oss.str();
}