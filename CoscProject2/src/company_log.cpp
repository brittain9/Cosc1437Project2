#include "company_log.h"

#include "client.h"
#include "employee.h"
#include "manager.h"
#include "project.h"

std::fstream CompanyLog::file;
std::vector<ILoggable*> CompanyLog::logs;


CompanyLog::CompanyLog(const std::string& filename) {
    file.open(filename, std::ios::in | std::ios::out | std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
}

CompanyLog::~CompanyLog() {
    if (file.is_open()) {
        file.close();
    }
}

void CompanyLog::readLines() {
    std::vector<std::string> linesRead;
    std::string line;
    file.seekg(0, std::ios::beg);
    while (getline(file, line)) {
        linesRead.push_back(line);
    }
    lines = linesRead;
}

void CompanyLog::parseLines() {
    for (std::string line : lines) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "Client") {
            int id;
            std::string name;
            std::string industry;
            std::vector<int> projectIDs;
            int projectID;

            iss >> id;
            std::getline(iss, name, '\"'); // Discard the first quote
            std::getline(iss, name, '\"'); // Read the name
            std::getline(iss, industry, '\"'); // Discard the space and first quote
            std::getline(iss, industry, '\"'); // Read the industry

            while (iss >> projectID) {
                projectIDs.push_back(projectID);
            }
            Client* client = new Client(id, name, industry, projectIDs);
            logs.push_back(client);
        }
        else if (type == "Project") {
            int id;
            std::string name;
            int status;
            double budget;
            double totalSpent;
            std::vector<int> employeesIds;
            int employeesId;

            iss >> id;
            std::getline(iss, name, '\"'); // Discard the first quote
            std::getline(iss, name, '\"'); // Read the name
            iss >> status >> budget >> totalSpent;

            while (iss >> employeesId) {
                employeesIds.push_back(employeesId);
            }
            Project* project = new Project(id, name, status, budget, totalSpent, employeesIds);
            logs.push_back(project);
        }
        else if (type == "Employee") {
            int id;
            std::string name;
            std::string position;
            int age;
            double salary;
            int history;
            int performance;

            iss >> id;
            std::getline(iss, name, '\"'); // Discard the first quote
            std::getline(iss, name, '\"'); // Read the name
            std::getline(iss, position, '\"'); // Discard the space and first quote
            std::getline(iss, position, '\"'); // Read the industry

            iss >> age >> salary >> history >> performance;
            
            Employee* employee = new Employee(id, name, position, age, salary, history, performance);
            logs.push_back(employee);
        }
        else if (type == "Manager") {
            int id;
            std::string name;
            std::string position;
            int age;
            double salary;
            int history;
            int performance;
            int levelInt;
            std::vector<int> employeeIDs;
            int employeeID;

            iss >> id;
            std::getline(iss, name, '\"'); // Discard the first quote
            std::getline(iss, name, '\"'); // Read the name
            std::getline(iss, position, '\"'); // Discard the space and first quote
            std::getline(iss, position, '\"'); // Read the industry

            iss >> age >> salary >> history >> performance >> levelInt;

            while (iss >> employeeID) {
                employeeIDs.push_back(employeeID);
            }

            // we need to cast out levelInt to the level_t enum
            level_t level = static_cast<level_t>(levelInt);

            Manager* manager = new Manager(id, name, position, age, salary, history, performance, level, employeeIDs);
            logs.push_back(manager);
        }
    }
}

void CompanyLog::addToLog(ILoggable* add) {
    int id = add->getId();
    bool found = false;

    // Iterate over the logs vector using a normal for loop
    for (size_t i = 0; i < logs.size(); ++i) {
        // If an object with the same ID is found, replace it
        if (logs[i]->getId() == id) {
            logs[i] = add; // Replace it with the new one
            found = true;
            break;
        }
    }

    // If no object with the same ID was found, add the new object to the end of the vector
    if (!found) {
        logs.push_back(add);
    }
}
void CompanyLog::removeFromLog(int id) {
    // Remove the object from the vector log
    for (size_t i = 0; i < logs.size(); ++i) {
        if (logs[i]->getId() == id) {
            logs.erase(logs.begin() + i);
            break;
        }
    }

    // Remove the object from the file log
    std::string line;
    std::ifstream fileIn("file.txt");
    std::ostringstream temp;
    bool found = false;

    while (std::getline(fileIn, line)) {
        std::istringstream iss(line);
        std::string currentType;
        int currentId;

        if (!(iss >> currentType >> currentId)) {
            break; // Error in reading the line
        }

        // If the ID matches, skip the line (do not write it to the temp buffer)
        if (currentId == id) {
            found = true;
        }
        else {
            // Keep the line as it is
            temp << line << "\n";
        }
    }

    fileIn.close();

    // Write the new content to the file
    std::ofstream fileOut("file.txt");
    fileOut << temp.str();
    fileOut.close();
}

std::vector<ILoggable*> CompanyLog::getInstancesOfType(std::string type) {
    std::vector<ILoggable*> result;

    for (int i = 0; i < logs.size(); i++) {

        if (type == "Client" && logs[i]->getClassName() == "Client") {
            Client* client = static_cast<Client*>(logs[i]);
            result.push_back(client);
        }
        else if (type == "Project" && logs[i]->getClassName() == "Project") {
            Project* project = static_cast<Project*>(logs[i]);
            result.push_back(project);
        }
        else if (type == "Employee" && logs[i]->getClassName() == "Employee") {
            Employee* employee = static_cast<Employee*>(logs[i]);
            result.push_back(employee);
        }
        else if (type == "Manager" && logs[i]->getClassName() == "Manager") {
            Manager* manager = static_cast<Manager*>(logs[i]);
            result.push_back(manager);
        }
    }
    return result;
}

std::vector<ILoggable*> CompanyLog::getInstancesFromIds(std::vector<int> ids) {
    std::vector<ILoggable*> result;

    for (int i = 0; i < logs.size(); i++) {

        for (int j = 0; j < ids.size(); j++) {

            if (ids[j] == logs[i]->getId()) {

                if (logs[i]->getClassName() == "Client") {
                    Client* client = static_cast<Client*>(logs[i]);
                    result.push_back(client);
                }
                else if (logs[i]->getClassName() == "Project") {
                    Project* project = static_cast<Project*>(logs[i]);
                    result.push_back(project);
                }
                else if (logs[i]->getClassName() == "Employee") {
                    Employee* employee = static_cast<Employee*>(logs[i]);
                    result.push_back(employee);
                }
            }
        }
    }
    return result;
}

// Method to write to file
void WriteToLog(ILoggable* toLog) {
    std::string type = toLog->getClassName();
    int id = toLog->getId();

    std::string line;
    std::ifstream fileIn("file.txt");
    std::ostringstream temp;
    bool found = false;

    // Read the file line by line
    while (std::getline(fileIn, line)) {
        std::istringstream iss(line);
        std::string currentType;
        int currentId;

        if (!(iss >> currentType >> currentId)) {
            break; // Error in reading the line
        }

        // Check if the type and id match
        if (currentType == type && currentId == id) {
            found = true;
            // Overwrite the line
            temp << toLog->createLogString() << "\n";
        }
        else {
            // Keep the line as it is
            temp << line << "\n";
        }
    }

    // If the type and id were not found, append to the end of the file
    if (!found) {
        temp << toLog->createLogString() << "\n";
    }

    fileIn.close();

    // Write the new content to the file
    std::ofstream fileOut("file.txt");
    fileOut << temp.str();
    fileOut.close();
}